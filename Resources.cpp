//
// Created by DELL on 13/07/2022.
//

#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {

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
        void (*deleter)(SDL_Texture *) = [] (SDL_Texture *texture) -> void {
            SDL_DestroyTexture(texture);
        };
        auto ptr = std::shared_ptr<SDL_Texture>(texture, deleter);
        imageTable.emplace(file, ptr);
        return ptr;
    }
}

void Resources::ClearImages() {
    for (auto & iT : imageTable) {
        const auto ptr = iT.second;
        if (ptr.unique()){
            imageTable.erase(iT.first);
        }
    }
    imageTable.clear();
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
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

        void (*deleter)(Mix_Music *) = [] (Mix_Music *music) -> void {
            Mix_FreeMusic(music);
        };
        auto ptr = std::shared_ptr<Mix_Music>(music, deleter);
        musicTable.emplace(file, ptr);
        return ptr;
    }
}

void Resources::ClearMusics() {
    for (auto & iT : musicTable) {
        const auto ptr = iT.second;
        if (ptr.unique()) {
            musicTable.erase(iT.first);
        }
    }
    musicTable.clear();
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {
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

        void (*deleter)(Mix_Chunk *) = [] (Mix_Chunk *sound) -> void {
            Mix_FreeChunk(sound);
        };

        auto ptr = std::shared_ptr<Mix_Chunk>(sound, deleter);
        soundTable.emplace(file, ptr);
        return ptr;
    }
}

void Resources::ClearSounds() {
    for (auto & iT : soundTable) {
        const auto ptr = iT.second;
        if (ptr.unique()) {
            soundTable.erase(iT.first);
        }
    }
    soundTable.clear();
}

std::shared_ptr<TTF_Font> Resources::GetFont(string file, int size) {
    auto key = file + std::to_string(size);
    if (fontTable.find(key) == fontTable.end()) {
        auto font = TTF_OpenFont(file.c_str(), size);

        void (*deleter)(TTF_Font *) = [] (TTF_Font *font) -> void {
            TTF_CloseFont(font);
        };

        auto ptr = std::shared_ptr<TTF_Font>(font, deleter);
        fontTable.emplace(key, ptr);
        return ptr;
    }
    return (*fontTable.find(key)).second;
}

void Resources::ClearFonts() {
    for (auto &iT : fontTable) {
        const auto ptr = iT.second;
        if (ptr.unique()) {
            fontTable.erase(iT.first);
        }
    }
    fontTable.clear();
}
