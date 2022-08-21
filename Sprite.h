//
// Created by DELL on 17/06/2022.
//
#pragma once
#include <string>
#include <SDL_image.h>
#include "Component.h"

using std::string;

class Sprite : public Component{
public:
    explicit Sprite(GameObject &associated);
    Sprite(GameObject &associated,const string& file);

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

private:
    SDL_Texture* texture;
    int width{};
    int height{};
    SDL_Rect clipRect{};
    Vec2 scale;
};