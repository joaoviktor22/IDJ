//
// Created by DELL on 04/07/2022.
//

#include "Vec2.h"
#include <cmath>

Vec2::Vec2() {
    X = 0;
    Y = 0;
}

Vec2::Vec2(float x, float y) {
    X = x;
    Y = y;
}

bool Vec2::Equals(const Vec2& vector) const {
    return vector.X == X && vector.Y == Y;
}

Vec2::~Vec2() = default;

Vec2 Vec2::operator+(const Vec2& soma) const {
    Vec2 result;
    result.X = X + soma.X;
    result.Y = Y + soma.Y;
    return result;
}

Vec2 Vec2::operator-(const Vec2& subtracao) const {
    Vec2 result;
    result.X = X - subtracao.X;
    result.Y = Y - subtracao.Y;
    return result;
}

Vec2 Vec2::operator*(const float escalar) const {
    Vec2 result;
    result.X = X*escalar;
    result.Y = Y*escalar;
    return result;
}

Vec2 Vec2::operator/(const float escalar) const {
    Vec2 result;
    result.X = X / escalar;
    result.Y = Y / escalar;
    return result;
}

float Vec2::Magnitude() const {
    return (float)std::sqrt(X*X + Y*Y);
}

Vec2 Vec2::Normalize() {
    float norm = Magnitude();
    return (*this) / norm;
}

float Vec2::GetDistance(const Vec2& destinyPoint) {
    Vec2 diferenceVector = (*this) - destinyPoint;
    return diferenceVector.Magnitude();
}

float Vec2::GetDistanceVectorAngle(const Vec2& destinyPoint) {
    Vec2 distanceVector = destinyPoint - (*this);
    return distanceVector.GetXAxisAngle();
}

float Vec2::GetXAxisAngle() const {
    return (float)std::atan2(Y, X);
}

void Vec2::Rotate(float angulo) {

    float previousX = X;

    X = previousX * std::cos(angulo) - Y * std::sin(angulo);
    Y = Y * std::cos(angulo) + previousX * std::sin(angulo);
}
