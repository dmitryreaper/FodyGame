#ifndef MUSIC_H
#define MUSIC_H

#include <SDL2/SDL_mixer.h>

Mix_Music* loadMusic(const char* filePath);
void playMusic(Mix_Music* music, int loops);
void stopMusic();

#endif
