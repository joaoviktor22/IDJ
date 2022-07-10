//
// Created by DELL on 04/07/2022.
//

#pragma once
#include <cmath>
#define PI 3.14159265
class Vec2 {
public:
    Vec2();
    Vec2(float x, float y);
    bool Equals(const Vec2& vector) const;
    ~Vec2();

    float X;
    float Y;

    Vec2 operator+(const Vec2& soma) const;
    Vec2 operator-(const Vec2& subtracao) const;
    Vec2 operator*(float escalar) const;
    Vec2 operator/(float escalar) const;

    float Magnitude() const;
    Vec2 Normalize();
    float GetDistance(const Vec2& otherPoint);
    float GetDistanceVectorAngle(const Vec2& destinyPoint);
    float GetXAxisAngle() const;
    void Rotate(float angulo);

};