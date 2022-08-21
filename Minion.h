//
// Created by DELL on 15/08/2022.
//

#ifndef JOGOCLIONV2_MINION_H
#define JOGOCLIONV2_MINION_H
#include "GameObject.h"

class Minion : public Component {
public:
    Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void Shoot(Vec2 target);
private:
    GameObject& alienCenter;
    float arc;
    float float_rand(float min, float max);
};


#endif //JOGOCLIONV2_MINION_H
