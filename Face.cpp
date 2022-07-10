//
// Created by DELL on 04/07/2022.
//

#include "Face.h"
#include "Sound.h"

Face::Face(GameObject &associated) : Component(associated) {
    this->hitpoints = 30;
}

void Face::Damage(int damage) {
    hitpoints = hitpoints - damage;
    if (hitpoints <= 0) {
        associated.RequestDelete();
        // Play sound if exist
        Component *SoundComponent = associated.GetComponent("Sound");
        if (SoundComponent) {
            auto *sound = dynamic_cast<Sound *>(SoundComponent);
            sound->Play(1);
        }
    }
}

void Face::Update(float dt) {

}

void Face::Render() {

}

bool Face::Is(std::string type) {
    return type == "Face";
}
