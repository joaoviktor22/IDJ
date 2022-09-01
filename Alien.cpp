//
// Created by DELL on 15/08/2022.
//

#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Minion.h"
#include "Game.h"
#include "Collider.h"
#include "Bullet.h"
#include "PenguinBody.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), speed({0, 0}), hp(40) {
    associated.AddComponent(new Sprite(associated, R"(D:\IDJ\JogoClion\img\alien.png)"));
    associated.AddComponent(new Collider(associated));
    minionArray.resize((unsigned long)(nMinions));
    alienCount++;
}

Alien::~Alien() {
    for (auto &i : minionArray) {
        i.lock()->RequestDelete();
    }
    minionArray.clear();
    alienCount--;
}

void Alien::Start() {
    std::weak_ptr<GameObject> weak_alien = Game::GetInstance().GetState().GetObjectPtr(&associated);
    auto nMinions = (float) minionArray.size();
    for (int i = 0; i < nMinions; i++){
        GameObject *minion = new GameObject();
        Minion *minion_behaviour = new Minion(*minion, weak_alien, (float)(2 * M_PI * (i / nMinions)));
        minion->AddComponent(minion_behaviour);

        minionArray[i] = (Game::GetInstance().GetState().AddObject(minion));
        restTimer = *new Timer;
    }
}

void Alien::Update(float dt) {
    if(hp <= 0){
        auto explosionGO(new GameObject());
        explosionGO->AddComponent(new Sprite(*explosionGO, R"(D:\IDJ\JogoClion\img\aliendeath.png)", 4, 0.1, 0.4));
        explosionGO->box.X = associated.box.GetCenter().X - explosionGO->box.W/2;
        explosionGO->box.Y = associated.box.GetCenter().Y - explosionGO->box.H/2;

        auto explosionSound(new Sound(*explosionGO, R"(D:\IDJ\JogoClion\audio\boom.wav)"));
        explosionGO->AddComponent(explosionSound);
        explosionSound->Play();

        Game::GetInstance().GetState().AddObject(explosionGO);

        associated.RequestDelete();
    } else{
        InputManager inputManager = InputManager::GetInstance();
        auto posX = (int)(inputManager.GetMouseX() + Camera::pos.X), posY = (int)(inputManager.GetMouseY() + Camera::pos.Y);
        associated.angleDeg += ALIEN_ROTATION_SPEED;

        PenguinBody *player = PenguinBody::player;
        if(player) {
            if (state == RESTING) {
                restTimer.Update(dt);
                if (restTimer.Get() > ALIEN_REST_COOLDOWN) {
                    destination = player->Posicao();
                    Vec2 vel = Vec2(ALIEN_SPEED, 0);
                    vel.Rotate((destination - associated.box.GetCenter()).GetXAxisAngle());
                    speed = vel;
                    state = MOVING;
                }
            } else {
                Vec2 deltaX = {ALIEN_SPEED * dt, 0};
                Vec2 calculado = destination - Vec2(associated.box.X + (associated.box.W / 2),
                                                    associated.box.Y + (associated.box.H / 2));
                Vec2 real = deltaX;
                real.Rotate(calculado.GetXAxisAngle());

                if (calculado.Magnitude() < real.Magnitude()) {
                    associated.box = associated.box + calculado;

                    auto target = player->Posicao();
                    const std::shared_ptr<GameObject> &ptr = minionArray[NearestMinion(target)].lock();
                    auto minion = (Minion *) (ptr->GetComponent("Minion"));
                    minion->Shoot(target);

                    state = RESTING;
                    restTimer.Restart();
                } else {
                    associated.box = associated.box + real;
                }

            }
        }
    }
}

void Alien::Render() {

}

bool Alien::Is(std::string type) {
    return type == "Alien";
}

int Alien::NearestMinion(const Vec2 &target) const {
    float minimum = ((*minionArray[0].lock()).box.GetCenter() - target).Magnitude();
    int location = 0;
    for(int i = 0; i < minionArray.size(); i++){
        float dist = ((*minionArray[i].lock()).box.GetCenter() - target).Magnitude();
        if (dist < minimum ){
            minimum = dist;
            location = i;
        }
    }
    return location;
}

void Alien::NotifyCollision(GameObject &other) {
    auto bullet = (Bullet*) other.GetComponent("Bullet");

    if (bullet && !bullet->targetsPlayer) {
        hp -= bullet->getDamage();
    }
}
