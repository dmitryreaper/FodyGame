#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "constants.h"

enum GameState {
    MENU,
    PLAYING,
    EXIT
};

void renderMenu(SDL_Renderer* renderer, int selectedItem);
void handleMenuEvents(SDL_Event& e, int* selectedItem, GameState* gameState, bool* quit);

#endif
