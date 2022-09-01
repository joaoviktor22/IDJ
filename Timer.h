//
// Created by DELL on 30/08/2022.
//
#pragma once

class Timer {
public:
    Timer();
    void Update(float dt);
    void Restart();
    float Get() const;
private:
    float time;
};