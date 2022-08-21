//
// Created by DELL on 15/08/2022.
//

#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Minion.h"
#include "Game.h"

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), speed({0, 0}), hp(40) {
    associated.AddComponent(new Sprite(associated, R"(D:\IDJ\JogoClion\img\alien.png)"));
    minionArray.resize((unsigned long)(nMinions));
}

Alien::~Alien() {
    for (auto &i : minionArray) {
        i.lock()->RequestDelete();
    }
    minionArray.clear();
}

void Alien::Start() {
    std::weak_ptr<GameObject> weak_alien = Game::GetInstance().GetState().GetObjectPtr(&associated);
    int nMinions = minionArray.size();
    for (int i = 0; i < nMinions; i++){
        GameObject *minion = new GameObject();
        Minion *minion_behaviour = new Minion(*minion, weak_alien, i * 360/nMinions);
        minion->AddComponent(minion_behaviour);

        minionArray[i] = (Game::GetInstance().GetState().AddObject(minion));
    }
}

void Alien::Update(float dt) {
    InputManager inputManager = InputManager::GetInstance();
    auto posX = (int)(inputManager.GetMouseX() + Camera::pos.X), posY = (int)(inputManager.GetMouseY() + Camera::pos.Y);

    if(inputManager.MousePress(LEFT_MOUSE_BUTTON)){
        taskQueue.push(*new Action(Action::SHOOT, posX , posY));
    } else if(inputManager.MousePress(RIGHT_MOUSE_BUTTON)){

        //impede de acumular eventos na fila, sobrescrevendo sempre que há um evento
        while(!taskQueue.empty()){
            taskQueue.pop();
        }
        taskQueue.push(*new Action(Action::MOVE, posX, posY));
    }

    if(!taskQueue.empty()){
        auto action = taskQueue.front();

        if(action.type == Action::MOVE){
            Vec2 deltaX = {500*dt, 0};
            Vec2 calculado = action.pos - Vec2(associated.box.X + (associated.box.W/2), associated.box.Y + (associated.box.H/2));
            deltaX.Rotate(calculado.GetXAxisAngle());

            if(calculado.Magnitude() < deltaX.Magnitude()){
                associated.box = associated.box + calculado;
                taskQueue.pop();
            } else {
                associated.box = associated.box + deltaX;
            }

        } else if(action.type == Action::SHOOT){
            auto target = InputManager::GetInstance().GetMouse();

            const std::shared_ptr<GameObject> &ptr = minionArray[NearestMinion(target)].lock();
            auto minion = (Minion*)(ptr->GetComponent("Minion"));
            minion->Shoot(target);

            taskQueue.pop();
            //auto closestMinion = NearestMinion(action.pos);
            //closestMinion->Shoot(action.pos);
            //taskQueue.pop();
        }
    }

    associated.angleDeg = associated.angleDeg - 2;

    if(hp <= 0){
        associated.RequestDelete();
    }
}

void Alien::Render() {

}

bool Alien::Is(std::string type) {
    return type == "Alien";
}

int Alien::NearestMinion(const Vec2 &target) const {
    float minimum = ((*minionArray[0].lock()).box.GetCenter() - target).Magnitude();
    int location = 0;
    for(int i = 0; i < minionArray.size(); i++){
        float dist = ((*minionArray[i].lock()).box.GetCenter() - target).Magnitude();
        if (dist < minimum ){
            minimum = dist;
            location = i;
        }
    }
    return location;
}

Alien::Action::Action(Alien::Action::ActionType type, float x, float y) : type(type) {
    pos.X = x;
    pos.Y = y;
}
