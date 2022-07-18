//
// Created by DELL on 13/07/2022.
//

#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture *Resources::GetImage(std::string file) {
    if (imageTable.find(file) != imageTable.end()) {
        return (*imageTable.find(file)).second;
    } else {
        Game& gameInstance = Game::GetInstance();
        SDL_Texture* texture = IMG_LoadTexture(gameInstance.GetRenderer(), file.c_str());
        if(texture == nullptr){
            string error = SDL_GetError();
            Log::LogError(error);
            exit(0);
        }

        imageTable.insert(make_pair(file, texture));
        return texture;
    }
}

void Resources::ClearImages() {
    for (auto & iT : imageTable) {
        SDL_DestroyTexture(iT.second);
    }
    imageTable.clear();
}

Mix_Music *Resources::GetMusic(std::string file) {
    if (musicTable.find(file) != musicTable.end()) {
        return (*musicTable.find(file)).second;
    } else {
        Game &gameInstance = Game::GetInstance();
        auto music = Mix_LoadMUS(file.c_str());
        if (music == nullptr) {
            string error = SDL_GetError();
            Log::LogError(error);
            exit(0);
        }

        musicTable.emplace(make_pair(file, music));
        return music;
    }
}

void Resources::ClearMusics() {
    for (auto & iT : musicTable) {
        Mix_FreeMusic(iT.second);
    }
    musicTable.clear();
}

Mix_Chunk *Resources::GetSound(std::string file) {
    if (soundTable.find(file) != soundTable.end()) {
        return (*soundTable.find(file)).second;
    } else {
        Game &gameInstance = Game::GetInstance();
        auto sound = Mix_LoadWAV(file.c_str());
        if (sound == nullptr) {
            string error = SDL_GetError();
            Log::LogError(error);
            exit(0);
        }

        soundTable.emplace(make_pair(file, sound));
        return sound;
    }
}

void Resources::ClearSounds() {
    for (auto & iT : soundTable) {
        Mix_FreeChunk(iT.second);
    }
    soundTable.clear();
}
