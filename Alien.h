//
// Created by DELL on 15/08/2022.
//

#ifndef JOGOCLIONV2_ALIEN_H
#define JOGOCLIONV2_ALIEN_H
#include "Component.h"
#include <queue>

class Alien : public Component {
public:
    Alien(GameObject &associated, int nMinions);
    ~Alien();
    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
private:
    class Action{
    public:
        enum ActionType{MOVE, SHOOT};
        Action(ActionType type, float x, float y);
        ActionType type;
        Vec2 pos;
    };
    Vec2 speed;
    int hp;
    std::queue<Action> taskQueue;
    std::vector<std::weak_ptr<GameObject>> minionArray;
    int NearestMinion(const Vec2 &target) const;
};


#endif //JOGOCLIONV2_ALIEN_H
