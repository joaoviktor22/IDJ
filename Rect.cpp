//
// Created by DELL on 04/07/2022.
//

#include "Rect.h"
Rect::Rect() {
    X = 0;
    Y = 0;
    W = 0;
    H = 0;
}

Rect::Rect(float x, float y, float w, float h) {
    X = x;
    Y = y;
    W = w;
    H = h;
}


Rect::~Rect() = default;

Rect Rect::operator+(const Vec2& vec) const {
    Rect result;

    result.X = X + vec.X;
    result.Y = Y + vec.Y;
    result.W = W;
    result.H = H;

    return result;
}

Vec2 Rect::GetCenter() const {
    Vec2 toReturn;

    toReturn.X = X + W / 2;
    toReturn.Y = Y + H / 2;

    return toReturn;
}

bool Rect::IsInside(const Vec2& coordinates) const {
    return coordinates.X >= X && coordinates.X <= X + W
           && coordinates.Y >= Y && coordinates.Y <= Y + H;
}

bool Rect::IsInside(float x, float y) const {
    return IsInside(Vec2(x, y));
}