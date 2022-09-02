//
// Created by DELL on 30/08/2022.
//
#pragma once
#include "Component.h"

#define PENGUIN_ACCELERATION 6
#define PENGUIN_SPEED_LIMIT 350
#define PENGUIN_ANGULAR_VELOCITY M_PI / 12

class PenguinBody : public Component {
public:
    explicit PenguinBody(GameObject &associated);
    virtual ~PenguinBody();

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    Vec2 Posicao();
    void NotifyCollision(GameObject &other) override;
    static PenguinBody* player;

private:
    std::weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;

};
