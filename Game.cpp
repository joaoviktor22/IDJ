//
// Created by DELL on 17/06/2022.
//
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Resources.h"
#include "InputManager.h"
#include "Game.h"
#include "State.h"

Game::Game(const string& title, int width, int height) {
    if (Instance != nullptr) {
        exit(0);
    }
    Instance = this;

    int statusCode = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);

    if (statusCode != 0) {
        string error = SDL_GetError();
        Log::LogError(error);
        exit(0);
    }

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    Mix_Init(MIX_INIT_OGG);

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_AllocateChannels(32);
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    storedState = new State();
}

Game* Game::Instance = nullptr;

Game & Game::GetInstance() {

    if (Instance == nullptr) {
        int width = DEFAULT_GAME_WIDTH;
        int height = DEFAULT_GAME_HEIGHT;
        return (*new Game("João Viktor 16/0127823", width, height));
    }

    return *Instance;
}

Game::~Game() {
    delete storedState;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();

    SDL_Quit();
}

State & Game::GetState() {
    return * storedState;
}

SDL_Renderer * Game::GetRenderer() {
    return renderer;
}

void Game::Run() {
    storedState->Start();
    while (!(*storedState).QuitRequested()) {
        CalculateDeltaTime();
        storedState->Render();
        InputManager::GetInstance().Update();
        storedState->Update(dt);
        SDL_RenderPresent(renderer);

        SDL_Delay(33);
    }
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}

float Game::GetDeltaTime() {
    return dt;
}

void Game::CalculateDeltaTime() {
    int actualTicks = SDL_GetTicks();
    dt = (actualTicks - frameStart) / 1000.0;
    frameStart = actualTicks;
}
