#pragma once

class Component;

#include <string>
#include "GameObject.h"

class Component{
public:
    explicit Component(GameObject &associated);
    virtual void Start();
    virtual ~Component();
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(std::string type) = 0;
    virtual void NotifyCollision (GameObject& other);

protected:
    GameObject& associated;
};