//
// Created by DELL on 15/08/2022.
//

#include "Bullet.h"
#include "Sprite.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite) : Component(associated) {
    associated.AddComponent(new Sprite(associated, sprite));
    Vec2 bala = Vec2(speed,0);
    bala.Rotate(angle);
    this->speed = bala;
    this->distanceLeft = maxDistance;
}

void Bullet::Update(float dt) {
    associated.box = associated.box + (speed * dt);
    distanceLeft -= (speed * dt).Magnitude();
    if(distanceLeft < 0){
        associated.RequestDelete();
    }
}

void Bullet::Render() {

}

bool Bullet::Is(std::string type) {
    return type == "Bullet";
}

int Bullet::getDamage() {
    return damage;
}
