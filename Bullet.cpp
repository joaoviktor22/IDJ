//
// Created by DELL on 15/08/2022.
//

#include "Bullet.h"
#include "Sprite.h"
#include "Collider.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetsPlayer) : Component(associated) {
    associated.AddComponent(new Sprite(associated, sprite, frameCount, frameTime));
    associated.AddComponent(new Collider(associated));
    associated.angleDeg = angle;
    Vec2 bala = Vec2(speed,0);
    bala.Rotate(angle);
    associated.angleDeg = associated.angleDeg * (180 / M_PI);
    this->speed = bala;
    this->distanceLeft = maxDistance;
    this->damage = damage;
    this->targetsPlayer = targetsPlayer;
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

void Bullet::NotifyCollision(GameObject &other) {
    if((other.GetComponent("Alien") && !targetsPlayer) || (other.GetComponent("PenguinBody") && targetsPlayer)){
        associated.RequestDelete();
    }
}