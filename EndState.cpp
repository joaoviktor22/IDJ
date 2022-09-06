//
// Created by DELL on 02/09/2022.
//

#include "EndState.h"
#include "Game.h"
#include "InputManager.h"
#include "TitleState.h"
#include "Text.h"
#include "GameData.h"
#include "Camera.h"

EndState::EndState() : State(){
    GameObject* endScreen = new GameObject();
    GameObject* firstMsg = new GameObject();

    Sprite* endScreenSprite;
    Text* firstMsgText;

    SDL_Color endTextColor;
    std::string conditionalText;
    if (GameData::playerVictory){
        endScreenSprite = new Sprite(*endScreen, R"(D:\IDJ\JogoClion\img\win.jpg)");
        conditionalText = "CONGRATULATIONS!!! You have won!";
        endTextColor = {0, 200, 0, 0};
        music.Open(R"(D:\IDJ\JogoClion\audio\endStateWin.ogg)");
    }
    else{
        endScreenSprite = new Sprite(*endScreen, R"(D:\IDJ\JogoClion\img\lose.jpg)");
        conditionalText = "Oh no! You have lost!";
        endTextColor = {200, 0, 0, 0};
        music.Open(R"(D:\IDJ\JogoClion\audio\endStateLose.ogg)");
    }
    std::string text = conditionalText;
    firstMsgText = new Text(*firstMsg, R"(D:\IDJ\JogoClion\font\Call me maybe.ttf)", 50, Text::BLENDED, text, endTextColor, 2);

    endScreen->AddComponent(endScreenSprite);
    firstMsg->AddComponent(firstMsgText);
    endScreen->box.X = Camera::pos.X;//704 pra 250 = 454
    endScreen->box.Y = Camera::pos.Y;//640 pra 368 = 272
    firstMsg->box.X = 1024/2 - Camera::pos.X - firstMsg->box.W/2;
    firstMsg->box.Y = 600 - Camera::pos.Y - firstMsg->box.H - 525;//offset de 525
    objectArray.emplace_back(endScreen);
    objectArray.emplace_back(firstMsg);

    GameObject* secondMsg = new GameObject();
    Text *secondMsgText = new Text(*secondMsg, R"(D:\IDJ\JogoClion\font\Call me maybe.ttf)", 40, Text::BLENDED, "Press ESC to go to Menu or SPACEBAR to play again", endTextColor, 2);
    secondMsg->AddComponent(secondMsgText);
    secondMsg->box.X = 1024/2 - Camera::pos.X - secondMsg->box.W/2 ;
    secondMsg->box.Y = 600 - Camera::pos.Y - secondMsg->box.H;

    objectArray.emplace_back(secondMsg);
}

EndState::~EndState() {
    music.Stop();
}

void EndState::LoadAssets() {

}

void EndState::Update(float dt) {
    if (InputManager::GetInstance().QuitRequested()){
        quitRequested = true;
    }
    if (InputManager::GetInstance().KeyPress(SDLK_ESCAPE)){
        TitleState* title = new TitleState();
        Game::GetInstance().Push(title);
        popRequested = true;
    }
    if (InputManager::GetInstance().KeyPress(SDLK_SPACE)){
        StageState* stage = new StageState();
        Game::GetInstance().Push(stage);
        popRequested = true;
    }
    UpdateArray(dt);
}

void EndState::Render() {
    RenderArray();
}

void EndState::Start() {
    StartArray();
    music.Play(-1);
}

void EndState::Pause() {
    music.Stop();
}

void EndState::Resume() {
    music.Play(-1);
}
