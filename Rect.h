//
// Created by DELL on 04/07/2022.
//

#pragma once
#include "Vec2.h"
class Rect {
public:
    Rect();
    Rect(float x, float y, float w, float h);
    ~Rect();

    float X,Y,W,H;

    Rect operator+(const Vec2& vec) const;

    Vec2 GetCenter() const;
    bool IsInside(const Vec2& coordinates) const;
    bool IsInside(float x, float y) const;

};