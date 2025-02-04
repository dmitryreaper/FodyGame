#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"
#include <SDL2/SDL_mixer.h> // Для работы с музыкой
#include <SDL2/SDL_image.h>

enum GameState {
    MENU,
    PLAYING,
    EXIT
};

void renderMenu(SDL_Renderer* renderer, int selectedItem);
void handleMenuEvents(SDL_Event &e, int *selectedItem, GameState *gameState,
                      bool *quit, Mix_Music *menuMusic, Mix_Music *gameMusic);

// Новые функции для работы с фоном
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);
void renderBackground(SDL_Renderer* renderer, SDL_Texture* backgroundTexture);

#endif
