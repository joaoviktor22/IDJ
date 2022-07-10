//
// Created by DELL on 17/06/2022.
//
#pragma once
#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include <string>
#include <SDL_mixer.h>


class Music{
public:
    Music();
    explicit Music(const std::string& file);

    void Play(int times);
    static void Stop();
    void Open(const std::string& file);
    bool IsOpen();

private:
    Mix_Music* music{};
};