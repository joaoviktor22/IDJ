//
// Created by DELL on 30/08/2022.
//

#include "PenguinCannon.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Sound.h"
#include "Game.h"
#include "Collider.h"
#include "Camera.h"

PenguinCannon::PenguinCannon(GameObject &associated, std::weak_ptr<GameObject> penguinBody) : Component(associated) , pbody(move(penguinBody)), angle(0) {
    associated.AddComponent(new Sprite(associated, R"(D:\IDJ\JogoClion\img\cubngun.png)"));
    associated.AddComponent(new Collider(associated));
}

void PenguinCannon::Update(float dt) {
//    GameObject &body = *pbody.lock();

//    if(body.IsDead()){
//        associated.RequestDelete();
//    }

//    InputManager &inputManager = InputManager::GetInstance();
//
//    associated.box = body.box;
//    associated.angleDeg = (inputManager.GetMouse() - associated.box.GetCenter()).GetXAxisAngle()* (float)(180 / M_PI);
//    angle = (float)associated.angleDeg;
    timer.Update(dt);
    auto go = pbody.lock();

    if (!go) {
        associated.RequestDelete();
    }
    else {
        Vec2 pos = go->box.GetCenter();
        InputManager& inputManager = InputManager::GetInstance();
        Vec2 mousePos = { (float) inputManager.GetMouseX() + Camera::pos.X,
                          (float) inputManager.GetMouseY() + Camera::pos.Y };

        angle = mousePos.GetXAxisAngle(pos);
        associated.angleDeg = angle * (180 / M_PI);
        associated.box.X = pos.X - associated.box.W / 2;
        associated.box.Y = pos.Y - associated.box.H / 2;

        if (inputManager.MousePress(
                LEFT_MOUSE_BUTTON) && timer.Get() > CANNON_COOLDOWN) {
            Shoot();
            timer.Restart();
        }
    }

//    if(inputManager.MousePress(LEFT_MOUSE_BUTTON)){
//        if(timer.Get() >= PENGUIN_SHOOT_COOLDOWN){//cooldown shoot
//            Shoot();
//            timer.Restart();
//        }
//    }
//    timer.Update(dt);
}

void PenguinCannon::Render() {

}

bool PenguinCannon::Is(std::string type) {
    return type == "PenguinCannon";
}

void PenguinCannon::Shoot() {
    auto bulletGo = new GameObject;
    Vec2 offset = Vec2(associated.box.W/2, 0);;
    offset.Rotate(angle);
    bulletGo->box.X = associated.box.GetCenter().X - bulletGo->box.W/2 + offset.X;
    bulletGo->box.Y = associated.box.GetCenter().Y - bulletGo->box.H/2 + offset.Y;

    bulletGo->AddComponent(new Bullet(*bulletGo, angle, 300, 10, 1000, R"(D:\IDJ\JogoClion\img\penguinbullet.png)", 4, 0.3, false));

    auto explosionSound(new Sound(*bulletGo, R"(D:\IDJ\JogoClion\audio\boom.wav)"));
    bulletGo->AddComponent(explosionSound);
    explosionSound->Play();
    Game::GetInstance().GetState().AddObject(bulletGo);
//    GameObject* go = new GameObject();
//    go->AddComponent(new Bullet(*go, angle, 300, 20, 1500, R"(D:\IDJ\JogoClion\img\penguinbullet.png)",4, 0.5, false));
//    Vec2 cannon_dist = Vec2(CANNON_DISTANCE, 0);
//    cannon_dist.Rotate(angle);
//    Vec2 cannonCenter = associated.box.GetCenter() + cannon_dist;
//    go->box.X = cannonCenter.X - go->box.W / 2;
//    go->box.Y = cannonCenter.Y - go->box.H / 2;
//    Game::GetInstance().GetState().AddObject(go);

}
