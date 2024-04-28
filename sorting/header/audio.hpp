#pragma once

#include "resources.hpp"

class Audio {
public:
    Audio();
    void play(float pitch);

private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
};