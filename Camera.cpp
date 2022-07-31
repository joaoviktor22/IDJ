//
// Created by DELL on 30/07/2022.
//

#include "Game.h"
#include "InputManager.h"
#include "Camera.h"

Vec2 Camera::pos = *new Vec2();
Vec2 Camera::speed(1000, 1000);
GameObject *Camera::focus = nullptr;

void Camera::Follow(GameObject *newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    float gameWidth = DEFAULT_GAME_WIDTH;
    float gameHeight = DEFAULT_GAME_HEIGHT;
    if(focus != nullptr){
        Vec2 center = focus->box.GetCenter();
        pos = {center.X - gameWidth/2, center.Y - gameHeight/2};
    } else {
        Vec2 direction;
        auto& input = InputManager::GetInstance();

        direction.X = input.IsKeyDown(LEFT_ARROW_KEY) ? -1 : 0;
        direction.X = input.IsKeyDown(RIGHT_ARROW_KEY) ? direction.X + 1 : direction.X;

        direction.Y = input.IsKeyDown(UP_ARROW_KEY) ? - 1 : 0;
        direction.Y = input.IsKeyDown(DOWN_ARROW_KEY) ? direction.Y + 1 : direction.Y;

        Vec2 deslocamento = speed*dt;
        deslocamento.X = deslocamento.X*direction.X;
        deslocamento.Y = deslocamento.Y*direction.Y;
        pos = pos + deslocamento;
    }
}
