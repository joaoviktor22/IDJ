//
// Created by DELL on 17/06/2022.
//

#include "State.h"

State::State() {
    quitRequested = false;
    bg = new Sprite(R"(D:\IDJ\JogoCLionv2\img\ocean.jpg)");
}

void State::LoadAssets() {
}

bool State::QuitRequested() const {
    return quitRequested;
}

void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();
}

void State::Render() {
    bg->Render(0, 0);
}