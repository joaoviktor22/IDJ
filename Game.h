//
// Created by DELL on 17/06/2022.
//

#pragma once
#include <iostream>
#include <string>
#include <SDL_image.h>
#include <stack>
#include "StageState.h"
#include "Log.h"

#define DEFAULT_GAME_WIDTH 1024;
#define DEFAULT_GAME_HEIGHT 600;

class Game {
public:
    Game(const std::string& title, int width, int height);
    ~Game();
    static Game& GetInstance();
    SDL_Renderer* GetRenderer();
    State& GetState();
    void Push(State *state);
    void Run();
    float GetDeltaTime() const;

private:
    static Game* Instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* storedState;
    std::stack<std::unique_ptr<State>>  stateStack;
    int frameStart;
    float dt;
    void CalculateDeltaTime();
};
//#ifndef JOGOCLIONV2_GAME_H
//#define JOGOCLIONV2_GAME_H

//#endif //JOGOCLIONV2_GAME_H
