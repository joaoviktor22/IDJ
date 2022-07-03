//
// Created by DELL on 17/06/2022.
//
#pragma once
#include <string>
#include <SDL_image.h>

using std::string;

class Sprite {
public:
    Sprite();
    Sprite(const string& file);

    ~Sprite();

    void Open(const string& file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    int GetWidth() const;
    int GetHeight() const;
    bool IsOpen();

private:
    SDL_Texture* texture;
    int width{};
    int height{};
    SDL_Rect clipRect{};
};