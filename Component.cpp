//
// Created by DELL on 04/07/2022.
//

#include "Component.h"

Component::Component(GameObject &associated) : associated(associated) {
}

void Component::Start() {

}

void Component::NotifyCollision(GameObject &other) {

}

Component::~Component() = default;