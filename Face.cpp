//
// Created by DELL on 04/07/2022.
//

#include "Face.h"
#include "Sound.h"
#include "Sprite.h"
#include "Camera.h"
#include "InputManager.h"

Face::Face(GameObject &associated) : Component(associated) {
    this->hitpoints = 30;
}

void Face::Damage(int damage) {
    hitpoints = hitpoints - damage;
    if (hitpoints <= 0) {
        Component *SoundComponent = associated.GetComponent("Sound");
        if (SoundComponent) {
            auto *sound = dynamic_cast<Sound *>(SoundComponent);
            //sound->Play(1);
            //if(Mix_Playing(sound->channel) != 1){
            //    associated.RequestDelete();
            //}
            Component *SpriteComponent = associated.GetComponent("Sprite");
            auto *sprite = dynamic_cast<Sprite *>(SpriteComponent);
            sound->Play(1);
            associated.RemoveComponent(sprite);
        }
    }
}

void Face::Update(float dt) {
    auto& inputManager = InputManager::GetInstance();
    float x = inputManager.GetMouseX() + Camera::pos.X;
    float y = inputManager.GetMouseY() + Camera::pos.Y;
    if (inputManager.MousePress(LEFT_MOUSE_BUTTON) && associated.box.IsInside(x,y)) {
        Damage(rand() % 10 + 10);
    }
}

void Face::Render() {

}

bool Face::Is(std::string type) {
    return type == "Face";
}
