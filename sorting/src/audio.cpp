#include "../header/audio.hpp"

Audio::Audio()
{
    if (!buffer.loadFromFile("beep.wav")) {
        std::cerr << "Failed to load audio file" << std::endl;
    }
    sound.setBuffer(buffer);
    sound.setLoop(false); // Sound will not loop
}

void Audio::play(float pitch) {
    sound.setPitch(pitch);
    sound.play();
}
