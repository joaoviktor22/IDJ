//
// Created by DELL on 04/07/2022.
//

#include "GameObject.h"
#include <algorithm>
#include <iostream>

GameObject::GameObject() {
    started = false;
    isDead = false;
    angleDeg = 0;
}

GameObject::~GameObject() {
    components.clear();
}

void GameObject::Update(float dt) {
    for (int i = 0; i < components.size(); i++) {
        components[i]->Update(dt);
    }
}

void GameObject::Render() {
    for (int i = 0; i < components.size(); i++) {
        components[i]->Render();
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
    for(int i = 0; i < components.size(); i++){
        if(components[i]->Is(type)){
            return components[i].get();
        }
    }
    return nullptr;
}

void GameObject::Start() {
    for (int i = 0; i < components.size(); i++) {
        components[i]->Start();
    }
    started = true;
}

void GameObject::NotifyCollision(GameObject &other) {
    for(auto & component : components){
        component->NotifyCollision(other);
    }
}
