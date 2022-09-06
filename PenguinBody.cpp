//
// Created by DELL on 30/08/2022.
//

#include "PenguinBody.h"
#include "Sprite.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "Camera.h"
#include "InputManager.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sound.h"

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated) , speed(0, 0), linearSpeed(0), angle(0), hp(100) {
    associated.AddComponent(new Sprite(associated, R"(D:\IDJ\JogoClion\img\penguin.png)"));
    associated.AddComponent(new Collider(associated));
    player = this;
}

PenguinBody::~PenguinBody() {
    player = nullptr;
}

void PenguinBody::Start() {
    auto *pcannonGO = new GameObject;
    pcannonGO->AddComponent(new PenguinCannon(*pcannonGO,Game::GetInstance().GetState().GetObjectPtr(&associated)));
    pcannon = Game::GetInstance().GetState().AddObject(pcannonGO);
}

void PenguinBody::Update(float dt) {
    InputManager& inputManager = InputManager::GetInstance();
    if (inputManager.IsKeyDown('a') || inputManager.IsKeyDown('d')) {
        int direction = inputManager.IsKeyDown('d') ? 1 : -1;
        angle += direction * PENGUIN_ANGULAR_VELOCITY;
        associated.angleDeg = angle * (180 / M_PI);
    }
    if (inputManager.IsKeyDown('w') || inputManager.IsKeyDown('s')) {
        int direction = inputManager.IsKeyDown('w') ? 1 : -1;
        linearSpeed += direction * PENGUIN_ACCELERATION;
        if (linearSpeed > PENGUIN_SPEED_LIMIT) {
            linearSpeed = PENGUIN_SPEED_LIMIT;
        }
        else if (linearSpeed < -PENGUIN_SPEED_LIMIT) {
            linearSpeed = -PENGUIN_SPEED_LIMIT;
        }
    }
    else {
        if (linearSpeed < 0) {
            linearSpeed =
                    linearSpeed > -PENGUIN_ACCELERATION ?
                    0 : linearSpeed + PENGUIN_ACCELERATION;
        }
        else if (linearSpeed > 0) {
            linearSpeed =
                    linearSpeed < PENGUIN_ACCELERATION ?
                    0 : linearSpeed - PENGUIN_ACCELERATION;
        }
    }
    if (linearSpeed) {
        Vec2 dir = { linearSpeed, 0 };
        dir.Rotate(angle);
        Vec2 result;
        result.X = associated.box.X + (dir.X * dt);
        result.Y = associated.box.Y + (dir.Y * dt);
        associated.box.X = result.X > 1380 ? 1380 : (result.X < 0 ? 0 : result.X);
        associated.box.Y = result.Y > 1280 ? 1280 : (result.Y < 0 ? 0 : result.Y);
        pcannon.lock()->box.X = associated.box.X;
        pcannon.lock()->box.Y = associated.box.Y;
    }
    if(hp <= 0){
        associated.RequestDelete();
        (*pcannon.lock()).RequestDelete();
        Camera::Unfollow();

        auto explosionGO(new GameObject());
        explosionGO->AddComponent(new Sprite(*explosionGO, R"(D:\IDJ\JogoClion\img\penguindeath.png)", 5, 0.1, 0.5));
        explosionGO->box.X = associated.box.GetCenter().X - explosionGO->box.W/2;
        explosionGO->box.Y = associated.box.GetCenter().Y - explosionGO->box.H/2;;

        auto explosionSound(new Sound(*explosionGO, R"(D:\IDJ\JogoClion\audio\boom.wav)"));
        explosionGO->AddComponent(explosionSound);
        explosionSound->Play();

        Game::GetInstance().GetState().AddObject(explosionGO);
    }
}

void PenguinBody::Render() {

}

bool PenguinBody::Is(std::string type) {
    return type == "PenguinBody";
}

Vec2 PenguinBody::Posicao() {
    return associated.box.GetCenter();
}
void PenguinBody::NotifyCollision(GameObject &other) {
    auto enemyBullet = (Bullet*) other.GetComponent("Bullet");

    if (enemyBullet && enemyBullet->targetsPlayer) {
        hp -= enemyBullet->getDamage();
    }
}