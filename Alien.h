//
// Created by DELL on 15/08/2022.
//
#pragma once
#ifndef JOGOCLIONV2_ALIEN_H
#define JOGOCLIONV2_ALIEN_H
#include "Component.h"
#include "Timer.h"
#include <queue>
#define ALIEN_SPEED 350
#define ALIEN_ROTATION_SPEED -2
#define ALIEN_REST_COOLDOWN 1.2

class Alien : public Component {
public:
    Alien(GameObject &associated, int nMinions, float timeOffset);
    ~Alien();
    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void NotifyCollision(GameObject &other) override;
    static int alienCount;
private:
    Vec2 speed;
    int hp;
    std::vector<std::weak_ptr<GameObject>> minionArray;
    int NearestMinion(const Vec2 &target) const;
    enum AlienState{MOVING, RESTING};
    AlienState state = RESTING;
    Timer restTimer;
    float timeOffset;
    Vec2 destination;
};


#endif //JOGOCLIONV2_ALIEN_H
