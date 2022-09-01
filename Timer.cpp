//
// Created by DELL on 30/08/2022.
//

#include "Timer.h"

Timer::Timer(): time(0){

}

void Timer::Update(float dt) {
    time = time + dt;
}

void Timer::Restart() {
    time = 0;
}

float Timer::Get() const {
    return time;
}

