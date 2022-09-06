//
// Created by DELL on 02/09/2022.
//

#include "State.h"
#include "Music.h"

class EndState : public State{
public:
    EndState();
    ~EndState();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
private:
    Music music;
};