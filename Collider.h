//
// Created by DELL on 30/08/2022.
//
#pragma once
#include "Component.h"

class Collider : public Component {
public:
    Collider(GameObject &associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});

    Rect box;

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    void setScale(const Vec2 &scale);
    void setOffset(const Vec2 &offset);

private:
    Vec2 scale;
    Vec2 offset;

};