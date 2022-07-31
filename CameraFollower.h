#pragma once
#include "Component.h"

class CameraFollower : public Component {
public:
    explicit CameraFollower(GameObject &associated);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
};