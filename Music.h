//
// Created by DELL on 17/06/2022.
//
#pragma once
#include <string>
#include <SDL_mixer.h>

using std::string;

class Music {
public:
    Music();
    explicit Music(const string& file);

    static void Play(int times);
    static void Stop();
    static void Open(const string& file);
    static bool IsOpen();

private:
    static Mix_Music* music;
};