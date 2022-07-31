//
// Created by DELL on 30/07/2022.
//

#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject &associated) : Component(associated) {

}

void CameraFollower::Update(float dt) {
    associated.box.X = Camera::pos.X;
    associated.box.Y = Camera::pos.Y;
}

void CameraFollower::Render() {

}

bool CameraFollower::Is(std::string type) {
    return type == "CameraFollower";
}
