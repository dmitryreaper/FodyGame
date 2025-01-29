#include "menu.h"
#include "music.h" 
#include <iostream>

void renderMenu(SDL_Renderer* renderer, int selectedItem) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    TTF_Font* font = TTF_OpenFont("DejaVuSerif.ttf", 48); // Загрузка шрифта
    if (!font) {
        std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color textColor = { 0, 0, 0, 255 };

    const char* menuItems[] = { "Start Game", "Exit" };
    for (int i = 0; i < 2; ++i) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, menuItems[i], textColor);
        if (!textSurface) {
            std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
            continue;
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);
        if (!textTexture) {
            std::cerr << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
            continue;
        }

        int x = SCREEN_WIDTH / 2 - textSurface->w / 2;
        int y = SCREEN_HEIGHT / 2 + i * 50 - 25;

        SDL_Rect renderQuad = { x, y, textSurface->w, textSurface->h };

        if (i == selectedItem) {
            SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF); // Выделение текущего пункта меню
            SDL_RenderFillRect(renderer, &renderQuad);
        }

        SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
        SDL_DestroyTexture(textTexture);
    }

    TTF_CloseFont(font);

    SDL_RenderPresent(renderer);
}

void handleMenuEvents(SDL_Event& e, int* selectedItem, GameState* gameState, bool* quit) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                *selectedItem = (*selectedItem > 0) ? *selectedItem - 1 : 1;
                break;
            case SDLK_DOWN:
                *selectedItem = (*selectedItem < 1) ? *selectedItem + 1 : 0;
                break;
            case SDLK_RETURN:
                if (*selectedItem == 0) {
                    stopMusic(); // Останавливаем музыку при выборе "Start Game"
                    *gameState = PLAYING;
                } else if (*selectedItem == 1) {
                    *quit = true; // Устанавливаем флаг завершения программы при выборе "Exit"
                    *gameState = EXIT;
                }
                break;
        }
    }
}
