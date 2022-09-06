//
// Created by DELL on 02/09/2022.
//

#include "TitleState.h"
#include "Sprite.h"
#include "Game.h"
#include "InputManager.h"
#include "Text.h"
#include "Camera.h"

TitleState::TitleState() : State(){
    auto titleGO(new GameObject);
    titleGO->AddComponent(new Sprite(*titleGO, R"(D:\IDJ\JogoClion\img\title.jpg)"));
    titleGO->box.X = Camera::pos.X;
    titleGO->box.Y = Camera::pos.Y;
    objectArray.emplace_back(titleGO);

    auto fontGO(new GameObject);
    Text *text = new Text(*fontGO, R"(D:\IDJ\JogoClion\font\Call me maybe.ttf)", 60, Text::TextStyle::BLENDED, "Press space to continue...", {255, 255, 255, 0});
    fontGO->AddComponent(text);
    Rect &fontBox = fontGO->box;
    fontBox.X = (float)1024/2 - fontBox.W/2 - Camera::pos.X;
    fontBox.Y = (float)600 - fontBox.H - Camera::pos.Y;
    objectArray.emplace_back(fontGO);
}
TitleState::~TitleState() {

}
void TitleState::Update(float dt) {
    auto inputManager = InputManager::GetInstance();

    UpdateArray(dt);

    quitRequested = inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY);
    if (inputManager.KeyPress(SDLK_SPACE)) {
        Game::GetInstance().Push(new StageState());
    }
}

void TitleState::LoadAssets() {

}

void TitleState::Render() {
    RenderArray();
}

void TitleState::Start() {
    StartArray();
}

void TitleState::Pause() {

}

void TitleState::Resume() {
    //Camera::pos = Vec2(0, 0);
}
