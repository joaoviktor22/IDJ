//
// Created by DELL on 17/06/2022.
//
#pragma once
#include "Sprite.h"
#include "Music.h"
#include "Face.h"
#include "Vec2.h"
#include "Sound.h"

class State {
public:
    State();
    ~State();
    void Input();
    void AddObject(int mouseX,int mouseY);
    bool QuitRequested() const;
    void LoadAssets();
    void Update(float dt);
    void Render();
private:
    Sprite bg;
    Music music;
    bool quitRequested;
    std::vector<std::unique_ptr<GameObject>> objectArray;
};