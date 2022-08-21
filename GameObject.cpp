//
// Created by DELL on 04/07/2022.
//

#include "GameObject.h"
#include <algorithm>

GameObject::GameObject() {
    started = false;
    isDead = false;
    angleDeg = 0;
}

GameObject::~GameObject() {
    components.clear();
}

void GameObject::Update(float dt) {
    for (auto &cpt: components) {
        cpt->Update(dt);
    }
}

void GameObject::Render() {
    for (auto &cpt: components) {
        cpt->Render();
    }
}

bool GameObject::IsDead() const {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component *cpt) {
    components.emplace_back(cpt);
    if(started){
        cpt->Start();
    }
}

void GameObject::RemoveComponent(Component* cpt) {
    components.erase(std::remove(components.begin(), components.end(), *new std::unique_ptr<Component>(cpt)));
    //components.erase(std::remove( components.begin(), components.end(), cpt), components.end() );
    //auto it = components.begin();
    //while(it != components.end()){
    //    if(*it == cpt){
    //        it = components.erase(it);
    //    }else{
    //        it++;
    //    }
    //}
}

Component *GameObject::GetComponent(const std::string& type) {
    Component *temp = nullptr;
    for (auto &cpt: components) {
        if (cpt->Is(type)) {
            temp = cpt.get();
        }
    }
    return temp;
}

void GameObject::Start() {
    for (auto &component : components) {
        component->Start();
    }
    started = true;
}
