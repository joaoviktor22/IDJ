//
// Created by DELL on 30/07/2022.
//

#include "InputManager.h"
#include <SDL.h>
#include <cstring>

InputManager::InputManager() {
    updateCounter = 0;
    mouseX = 0;
    mouseY = 0;
    quitRequested = false;
    memset(mouseState, 0, sizeof(mouseState));
    memset(mouseUpdate, 0, sizeof(mouseUpdate));
}

InputManager::~InputManager() = default;

void InputManager::Update() {
    SDL_Event event;
    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    updateCounter++;
    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT) {
            quitRequested = true;

        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            mouseState[event.button.button] = true;
            mouseUpdate[event.button.button] = updateCounter;

        } else if (event.type == SDL_MOUSEBUTTONUP) {
            mouseState[event.button.button] = false;
            mouseUpdate[event.button.button] = updateCounter;

        } else if (event.type == SDL_KEYDOWN) {
            if (!event.key.repeat) {
                auto keyPressed = event.key.keysym.sym;
                keyState[keyPressed] = true;
                keyUpdate[keyPressed] = updateCounter;
            }

        } else if (event.type == SDL_KEYUP) {
            auto keyPressed = event.key.keysym.sym;
            keyState[keyPressed] = false;
            keyUpdate[keyPressed] = updateCounter;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::KeyRelease(int key) {
    return !keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

bool InputManager::MousePress(int button) {
    return mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::MouseRelease(int button) {
    return !mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}

InputManager &InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}
