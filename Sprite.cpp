//
// Created by DELL on 17/06/2022.
//

#include "Sprite.h"
#include "Resources.h"
#include "Game.h"
#include "Camera.h"

Sprite::Sprite(GameObject &associated) : Component(associated) {
    texture = nullptr;
    scale = Vec2(1,1);
    frameCount = 1;
    frameTime = 1;
    currentFrame = 0;
    timeElapsed = 0;
    secondsToSelfDestruct = 0;
    selfDestructCount = *new Timer;

}

Sprite::Sprite(GameObject &associated,const string& file, int frameCount, float frameTime, float secondsToSelfDestruct) : Component(associated) {
    this->frameTime = frameTime;
    this->frameCount = frameCount;
    currentFrame = 0;
    timeElapsed = 0;
    this->secondsToSelfDestruct = secondsToSelfDestruct;
    selfDestructCount = *new Timer;
    texture = nullptr;
    scale = Vec2(1,1);
    Open(file);
    //associated.box.W = width;
    //associated.box.H = height;
}


Sprite::~Sprite() {
    //if (texture!=nullptr) {
    //    SDL_DestroyTexture(texture);
    //}
}

void Sprite::Open(const string& file) {
    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    associated.box.W = width;
    associated.box.H = height;
    SetClip(0, 0, width / frameCount, height);
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
    destinyRectangle.h = clipRect.h * scale.X;
    destinyRectangle.w = clipRect.w * scale.X;
    if(associated.GetComponent("Bullet")){
        //associated.angleDeg = associated.angleDeg * (180 / M_PI);
    }
    SDL_RenderCopyEx(renderer, texture.get(), &clipRect, &destinyRectangle, associated.angleDeg, nullptr , SDL_FLIP_NONE);
    if(associated.GetComponent("Bullet")){
        //associated.angleDeg = associated.angleDeg / (180 / M_PI);
    }
}

int Sprite::GetWidth() const {
    return (int)((width*scale.X)/frameCount);
}

int Sprite::GetHeight() const {
    return (int)(height*scale.Y);
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}

void Sprite::Render() {
    Render(static_cast<int>(associated.box.X - (int)Camera::pos.X), static_cast<int>(associated.box.Y - (int)Camera::pos.Y));
}

void Sprite::Update(float dt) {
    if(secondsToSelfDestruct > 0){
        selfDestructCount.Update(dt);
        if(selfDestructCount.Get() > secondsToSelfDestruct){
            associated.RequestDelete();
        }
    }
    timeElapsed += dt;
    if (timeElapsed >= frameTime){
        SetFrame(currentFrame + 1);
    }
    if (currentFrame >= frameCount){
        SetFrame(0);
    }
}


bool Sprite::Is(std::string type) {
    return type == "Sprite";
}

void Sprite::SetScale(float scaleX, float scaleY) {
    auto &box = associated.box;
    if(scaleX != 0){
        scale.X = scaleX;
        box.W = (width / frameCount) * scaleX;
        box.X = box.GetCenter().X - box.W/2;
    }

    if(scaleY != 0){
        scale.Y = scaleY;
        box.H = height * scaleY;
        box.Y = box.GetCenter().Y - box.H/2;
    }
}

Vec2 Sprite::GetScale() {
    return scale;
}

void Sprite::SetFrame(int frame){
    this->currentFrame = frame;
    SetClip(frame * GetWidth(), 0, clipRect.w, clipRect.h);
}

void Sprite::SetFrameCount(int frameCount){
    this->frameCount = frameCount;
    SetFrame(0);
    associated.box.W = GetWidth();
    SetClip(0, clipRect.y, GetWidth(), clipRect.h);
}

void Sprite::SetFrameTime(float frameTime){
    this->frameTime = frameTime;
}
