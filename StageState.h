//
// Created by DELL on 17/06/2022.
//
#pragma once


#include "TileSet.h"
#include "State.h"
#include "Music.h"

class StageState : public State{
public:
    StageState();
    ~StageState();
    void LoadAssets() override;
    void Update(float dt) override;
    void Render() override;
    void Start() override;
    void Pause() override;
    void Resume() override;
private:
    Music music;
    TileSet* tileSet;
};