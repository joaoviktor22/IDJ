//
// Created by DELL on 17/06/2022.
//

#include "Music.h"

Music::Music() {
    music = nullptr;
}

Music::Music(const std::string& file) {
    Open(file);
}

void Music::Play(int times) {
    Mix_PlayMusic(music, times);
}

void Music::Stop() {
    Mix_FadeOutMusic(0);
}

void Music::Open(const std::string& file) {
    music = Mix_LoadMUS(file.c_str());
}

bool Music::IsOpen() {
    return music != nullptr;
}