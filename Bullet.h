//
// Created by DELL on 15/08/2022.
//

#ifndef JOGOCLIONV2_BULLET_H
#define JOGOCLIONV2_BULLET_H
#include "Component.h"

class Bullet : public Component {
public:
    Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    int getDamage();
private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};


#endif //JOGOCLIONV2_BULLET_H
