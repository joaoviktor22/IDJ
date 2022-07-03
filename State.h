//
// Created by DELL on 17/06/2022.
//
#pragma once
#include "Sprite.h"
#include "Music.h"

class State {
public:
    State();

    bool QuitRequested() const;
    void LoadAssets();
    void Update(float dt);
    void Render();
private:
    Sprite* bg;
    Music* music;
    bool quitRequested;
};