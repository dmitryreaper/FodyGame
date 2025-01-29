#include "music.h"
#include <iostream>

Mix_Music* loadMusic(const char* filePath) {
    Mix_Music* music = Mix_LoadMUS(filePath);
    if (music == nullptr) {
        std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    return music;
}

void playMusic(Mix_Music* music, int loops) {
    if (music != nullptr) {
        if (Mix_PlayMusic(music, loops) == -1) {
            std::cerr << "Failed to play music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        }
    }
}

void stopMusic() {
    Mix_HaltMusic();
}
