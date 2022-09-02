//
// Created by DELL on 30/08/2022.
//

#pragma once
#include "Component.h"
#include "Timer.h"

#define CANNON_COOLDOWN 1

class PenguinCannon :public Component {
public:
    PenguinCannon(GameObject &associated, std::weak_ptr<GameObject> penguinBody);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void Shoot();

private:
    std::weak_ptr<GameObject> pbody;
    float angle;
    Timer timer;
};
