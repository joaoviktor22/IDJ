#pragma once

class GameObject;

#include "Component.h"
#include <vector>
#include <string>
#include "Rect.h"
#include <memory>

class GameObject{
public:
    GameObject();
    ~GameObject();
    void Update(float dt);
    void Render();
    bool IsDead() const;
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(const std::string& type);
    Rect box;
private:
    //std::vector<Component*> components;
    std::vector<std::unique_ptr<Component>> components;
    bool isDead;
};