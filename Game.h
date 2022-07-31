//
// Created by DELL on 17/06/2022.
//

#pragma once
#include <iostream>
#include <string>
#include <SDL_image.h>
#include "State.h"
#include "Log.h"

using std::string;

#define DEFAULT_GAME_WIDTH 1024;
#define DEFAULT_GAME_HEIGHT 600;

class Game {
public:
    Game(const string& title, int width, int height);
    ~Game();
    static Game& GetInstance();
    SDL_Renderer* GetRenderer();
    State& GetState();
    void Run();
    float GetDeltaTime();

private:
    static Game* Instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* storedState;
    int frameStart;
    float dt;
    void CalculateDeltaTime();
};
//#ifndef JOGOCLIONV2_GAME_H
//#define JOGOCLIONV2_GAME_H

//#endif //JOGOCLIONV2_GAME_H
