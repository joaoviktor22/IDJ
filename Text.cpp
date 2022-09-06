//
// Created by DELL on 02/09/2022.
//

#include "Text.h"
#include "Game.h"
#include "Camera.h"
#include "Resources.h"

Text::Text(GameObject &associated, std::string fontFile, int fontSize, Text::TextStyle style, std::string text, SDL_Color color, int blinkPeriod) : Component(associated), font(nullptr), texture(nullptr), text(text), style(style), fontFile(fontFile.c_str()), fontSize(fontSize), color(color){
    RemakeTexture();
}

Text::~Text() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt) {

}

void Text::Render() {
    SDL_Rect clipRect = {0, 0, (int)associated.box.W, (int)associated.box.H};
    SDL_Rect dst = {(int)associated.box.X + (int)Camera::pos.X,(int)associated.box.Y + (int)Camera::pos.Y,clipRect.w,clipRect.h};
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dst, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

bool Text::Is(std::string type) {
    return type == "Text";
}

void Text::SetText(std::string text) {
    this->text = move(text);
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(Text::TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(std::string fontFile) {
    fontFile = move(fontFile);
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
    font = Resources::GetFont(fontFile, fontSize);
    SDL_Surface *surface;
    if(style == TextStyle::SOLID){
        surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
    }else if(style == TextStyle::SHADED){
        surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, { 0, 0, 0, 255 });
    }else if(style == TextStyle::BLENDED){
        surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
    }
    int tempWidth, tempHeight;
    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &tempWidth, &tempHeight);

    associated.box.W = tempWidth;
    associated.box.H = tempHeight;
    SDL_FreeSurface(surface);
}
