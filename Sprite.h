//
// Created by DELL on 17/06/2022.
//
#pragma once
#include <string>
#include <SDL_image.h>
#include "Component.h"
#include "Timer.h"

using std::string;

class Sprite : public Component{
public:
    explicit Sprite(GameObject &associated);
    Sprite(GameObject &associated,const string& file,int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);

    ~Sprite() override;

    void Open(const string& file);
    void SetClip(int x, int y, int w, int h);
    void Render() override;
    void Render(int x, int y);
    int GetWidth() const;
    int GetHeight() const;
    bool IsOpen();
    void Update(float dt) override;
    bool Is(std::string type) override;
    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale();
    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);
private:
    SDL_Texture* texture;
    int width{};
    int height{};
    SDL_Rect clipRect{};
    Vec2 scale;
    int frameCount;
    int currentFrame;
    float timeElapsed;
    float frameTime;
    Timer selfDestructCount;
    float secondsToSelfDestruct;
};