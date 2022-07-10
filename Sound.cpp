//
// Created by DELL on 04/07/2022.
//

#include "Sound.h"

Sound::Sound(GameObject &associated) : Component(associated) {
    chunk = nullptr;
}

Sound::Sound(GameObject &associated, const std::string& file):Sound(associated) {
    Open(file);
}

Sound::~Sound() {
    if (chunk) {
        Mix_FreeChunk(chunk);
    }
}

void Sound::Play(int times) {

    channel = Mix_PlayChannel(-1, chunk, times - 1);
}

void Sound::Stop() {
    if (chunk) {
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(const std::string& file) {
    chunk = Mix_LoadWAV(file.c_str());
}

bool Sound::IsOpen() {
    return false;
}

void Sound::Update(float dt) {

}

void Sound::Render() {

}

bool Sound::Is(std::string type) {
    return type == "Sound";
}