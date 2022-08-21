//
// Created by DELL on 15/08/2022.
//

#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"

Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(*alienCenter.lock()), arc(arcOffsetDeg) {
    Sprite *sprite = new Sprite(associated, R"(D:\IDJ\JogoClion\img\minion.png)");
    float random = float_rand(1, 1.5f);
    sprite->SetScale(random, random);
    associated.AddComponent(sprite);
}

void Minion::Update(float dt) {
    if(associated.IsDead()){
        associated.RequestDelete();
    }
    arc += (M_PI/4) * dt;
    Vec2 raioOrbita(150,0);
    raioOrbita.Rotate(arc);
    Vec2 distOrigem = alienCenter.box.GetCenter();

    associated.box = associated.box + (raioOrbita - associated.box.GetCenter() + distOrigem);
    associated.angleDeg = raioOrbita.GetXAxisAngle() * 180 / M_PI;
}

void Minion::Render() {

}

bool Minion::Is(std::string type) {
    return type == "Minion";
}

void Minion::Shoot(Vec2 target) {
    auto bulletGo = new GameObject;
    bulletGo->box.X = associated.box.GetCenter().X - bulletGo->box.W/2;
    bulletGo->box.Y = associated.box.GetCenter().Y - bulletGo->box.H/2;
    float angle = (target - associated.box.GetCenter()).GetXAxisAngle();
    bulletGo->angleDeg = angle * 180 / M_PI;
    bulletGo->AddComponent(new Bullet(*bulletGo, angle, 800, 22, 2000, R"(D:\IDJ\JogoClion\img\minionbullet1.png)"));

    Game::GetInstance().GetState().AddObject(bulletGo);
}

float Minion::float_rand(float min, float max) {
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}
