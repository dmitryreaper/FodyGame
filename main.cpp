#include <SDL2/SDL.h>
#include <iostream>
#include <vector> // Для хранения списка врагов
#include "Dot.h"
#include "menu.h"
#include "music.h"
#include "constants.h"
#include "Enemy.h" // Подключаем класс Enemy

// Прототип функции для проверки столкновений
bool isColliding(const Dot& dot, const Enemy& enemy);

int main(int /*argc*/, char* /*args*/[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) { // Инициализируем видео и аудио
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() == -1) { // Инициализация SDL_ttf
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) { // Инициализация SDL_mixer
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Move the Dot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event e;
    int selectedItem = 0;
    GameState gameState = MENU;
    bool keys[4] = {false, false, false, false}; // W, S, A, D
    Dot dot(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    Uint32 lastFrameTime = SDL_GetTicks(); // Время начала первого кадра

    Mix_Music* music = loadMusic("music.mp3");
    if (music == nullptr) {
        std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    } else {
        playMusic(music, -1); // -1 означает бесконечное воспроизведение
    }

    // Создаем список врагов
    std::vector<Enemy> enemies;
    enemies.emplace_back(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4); // Первый враг
    enemies.emplace_back(3 * SCREEN_WIDTH / 4, 3 * SCREEN_HEIGHT / 4); // Второй враг

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
                gameState = EXIT;
            }
            if (gameState == MENU) {
                handleMenuEvents(e, &selectedItem, &gameState, &quit); // Передаем флаг quit в функцию обработки событий
            } else if (gameState == PLAYING) {
                if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                    switch (e.key.keysym.sym) {
                        case SDLK_w: keys[0] = true; break;
                        case SDLK_s: keys[1] = true; break;
                        case SDLK_a: keys[2] = true; break;
                        case SDLK_d: keys[3] = true; break;
                    }
                } else if (e.type == SDL_KEYUP) {
                    switch (e.key.keysym.sym) {
                        case SDLK_w: keys[0] = false; break;
                        case SDLK_s: keys[1] = false; break;
                        case SDLK_a: keys[2] = false; break;
                        case SDLK_d: keys[3] = false; break;
                    }
                }
            }
        }

        if (gameState == MENU) {
            renderMenu(renderer, selectedItem);
        } else if (gameState == PLAYING) {
            Uint32 currentTime = SDL_GetTicks();
            Uint32 deltaTime = currentTime - lastFrameTime;
            lastFrameTime = currentTime;

            // Движение игрока
            dot.move(keys, deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT);

            // Обновляем позиции всех врагов
            for (auto& enemy : enemies) {
                enemy.updatePosition(dot, deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT);
            }

            // Проверяем столкновения с врагами
            for (const auto& enemy : enemies) {
                if (isColliding(dot, enemy)) {
                    std::cout << "Game Over!" << std::endl;
                    quit = true;
                    gameState = EXIT;
                    break;
                }
            }

            // Отрисовка
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);

            dot.render(renderer);

            // Рисуем всех врагов
            for (const auto& enemy : enemies) {
                enemy.render(renderer);
            }

            SDL_RenderPresent(renderer);

            // Ограничиваем количество кадров в секунду до 60 FPS
            SDL_Delay(16);
        }
    }

    // Освобождаем ресурсы
    if (music != nullptr) {
        Mix_FreeMusic(music);
        music = nullptr;
    }

    Mix_CloseAudio();
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

// Функция для проверки столкновений между игроком и врагом
bool isColliding(const Dot& dot, const Enemy& enemy) {
    return (dot.getX() < enemy.getX() + ENEMY_SIZE &&
            dot.getX() + DOT_SIZE > enemy.getX() &&
            dot.getY() < enemy.getY() + ENEMY_SIZE &&
            dot.getY() + DOT_SIZE > enemy.getY());
}
