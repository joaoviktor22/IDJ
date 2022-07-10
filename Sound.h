//
// Created by DELL on 04/07/2022.
//

#ifndef JOGOCLIONV2_SOUND_H
#define JOGOCLIONV2_SOUND_H

#include <SDL_mixer.h>
#include "Component.h"

class Sound : public Component{
public:
    explicit Sound(GameObject &associated);
    Sound(GameObject &associated, const std::string& file);
    ~Sound() override;
    void Play(int times = -1);
    void Stop();
    void Open(const std::string& file);
    static bool IsOpen();

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
private:
    Mix_Chunk *chunk;
    int channel{};
};


#endif //JOGOCLIONV2_SOUND_H
