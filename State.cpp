//
// Created by DELL on 02/09/2022.
//

#include "State.h"

State::State() : popRequested(false), quitRequested(false), started(false){

}

State::~State() {
    objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject *object) {
    std::shared_ptr<GameObject> gameObject(object);
    objectArray.push_back(gameObject);
    if(started){
        gameObject->Start();
    }
    return std::weak_ptr<GameObject>(gameObject);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *object) {
    for (auto &i : objectArray) {
        if(i.get() == object){
            return std::weak_ptr<GameObject>(i);
        }
    }
    return std::weak_ptr<GameObject>();
}

bool State::PopRequested() {
    return popRequested;
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::StartArray() {
    for (int i = 0; i < objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
}

void State::UpdateArray(float dt) {
    for (int i = 0; i < objectArray.size(); i++){
        objectArray[i]->Update(dt);
    }
}

void State::RenderArray() {
    for (int i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}
