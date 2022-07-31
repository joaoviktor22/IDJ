//
// Created by DELL on 17/06/2022.
//

#include "Sprite.h"
#include "Resources.h"
#include "Game.h"
#include "Camera.h"

Sprite::Sprite(GameObject &associated) : Component(associated) {
    texture = nullptr;
}

Sprite::Sprite(GameObject &associated,const string& file) : Component(associated) {
    texture = nullptr;
    Open(file);
    //associated.box.W = width;
    //associated.box.H = height;
    //scale.X = 1;
    //scale.Y = 1;
}


Sprite::~Sprite() {
    //if (texture!=nullptr) {
    //    SDL_DestroyTexture(texture);
    //}
}

void Sprite::Open(const string& file) {
    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    associated.box.W = width;
    associated.box.H = height;
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    SDL_Rect destinyRectangle;

    destinyRectangle.x = x;
    destinyRectangle.y = y;
    destinyRectangle.h = clipRect.h;
    destinyRectangle.w = clipRect.w;

    SDL_RenderCopy(renderer, texture, &clipRect, &destinyRectangle);
}

int Sprite::GetWidth() const {
    return width;
}

int Sprite::GetHeight() const {
    return height;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}

void Sprite::Render() {
    Render(static_cast<int>(associated.box.X - (int)Camera::pos.X), static_cast<int>(associated.box.Y - (int)Camera::pos.Y));
}

void Sprite::Update(float dt) {}


bool Sprite::Is(std::string type) {
    return type == "Sprite";
}
