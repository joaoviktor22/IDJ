//
// Created by DELL on 04/07/2022.
//

#ifndef JOGOCLIONV2_FACE_H
#define JOGOCLIONV2_FACE_H

#include "Component.h"

class Face : public Component{
public:
    explicit Face(GameObject& associated);
    void Damage(int damage);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    int hitpoints;
};


#endif //JOGOCLIONV2_FACE_H
