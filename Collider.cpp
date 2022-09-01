//
// Created by DELL on 30/08/2022.
//

#include "Collider.h"
#include "Camera.h"
#include "Game.h"

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated), scale(scale), offset(offset) {

}

void Collider::Update(float dt) {
    Rect aux = Rect();

    aux.W = associated.box.W * scale.X;
    aux.H = associated.box.H * scale.Y;

    const Vec2 &center = associated.box.GetCenter();
    aux.X = center.X - aux.W/2;
    aux.Y = center.Y - aux.H/2;
    offset.Rotate((float)(associated.angleDeg));
    box = aux + offset;
}

void Collider::Render() {
//    Vec2 center( box.GetCenter() );
//	SDL_Point points[5];
//    Vec2 p1 = Vec2(box.X, box.Y) - center;
//    p1.Rotate(associated.angleDeg/(180/PI) );
//	Vec2 point = p1 + center - Camera::pos;
//	points[0] = {(int)point.X, (int)point.Y};
//	points[4] = {(int)point.X, (int)point.Y};
//
//    Vec2 p2 = Vec2(box.X + box.W, box.Y) - center;
//    p2.Rotate(associated.angleDeg/(180/PI) );
//	point = p2 + center - Camera::pos;
//	points[1] = {(int)point.X, (int)point.Y};
//
//    Vec2 p3 = Vec2(box.X + box.W, box.Y + box.H) - center;
//    p3.Rotate(associated.angleDeg/(180/PI) );
//	point = p3 + center - Camera::pos;
//	points[2] = {(int)point.X, (int)point.Y};
//
//    Vec2 p4 = Vec2(box.X, box.Y + box.H) - center;
//    p4.Rotate(associated.angleDeg/(180/PI) );
//	point = p4 + center - Camera::pos;
//	points[3] = {(int)point.X, (int)point.Y};
//
//	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
//	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
}

bool Collider::Is(std::string type) {
    return type == "Collider";
}

void Collider::setScale(const Vec2 &scale) {
    this->scale = scale;
}

void Collider::setOffset(const Vec2 &offset) {
    this->offset = offset;
}
