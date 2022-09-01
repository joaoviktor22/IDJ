//
// Created by DELL on 15/08/2022.
//
#pragma once
#ifndef JOGOCLIONV2_BULLET_H
#define JOGOCLIONV2_BULLET_H
#include "Component.h"

class Bullet : public Component {
public:
    Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetsPlayer);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void NotifyCollision(GameObject &other) override;
    int getDamage();
    bool targetsPlayer;
private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};


#endif //JOGOCLIONV2_BULLET_H
