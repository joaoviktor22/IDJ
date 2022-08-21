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
    std::weak_ptr<GameObject> AddObject(GameObject* go);
    bool QuitRequested() const;
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
private:
    //Sprite bg;
    bool started;
    Music music;
    bool quitRequested;
    std::vector<std::shared_ptr<GameObject>> objectArray;
};