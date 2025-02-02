#include "Dot.h"
#include <iostream>
#include "constants.h"

// Конструктор dot
Dot::Dot(int x, int y) : mPosX(x), mPosY(y), mVelX(0), mVelY(0) {}

// Обработка событий клавиатуры
void Dot::handleEvent(SDL_Event& e, bool* keys) {
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

// Движение точки
void Dot::move(bool* keys, Uint32 deltaTime, int screenWidth, int screenHeight) {
    float accelerationFactor = ACCELERATION * (deltaTime / 1000.0f);
    float decelerationFactor = DECELERATION * (deltaTime / 1000.0f);

    // Ускорение при нажатии на клавиши
    if (keys[0]) mVelY -= accelerationFactor;
    if (keys[1]) mVelY += accelerationFactor;
    if (keys[2]) mVelX -= accelerationFactor;
    if (keys[3]) mVelX += accelerationFactor;

    // Замедление при отпускании клавиш
    if (!keys[0] && !keys[1]) {
        if (mVelY > 0) mVelY -= decelerationFactor;
        if (mVelY < 0) mVelY += decelerationFactor;
    }
    if (!keys[2] && !keys[3]) {
        if (mVelX > 0) mVelX -= decelerationFactor;
        if (mVelX < 0) mVelX += decelerationFactor;
    }

    // Ограничение скорости
    if (mVelX > MAX_SPEED) mVelX = MAX_SPEED;
    if (mVelX < -MAX_SPEED) mVelX = -MAX_SPEED;
    if (mVelY > MAX_SPEED) mVelY = MAX_SPEED;
    if (mVelY < -MAX_SPEED) mVelY = -MAX_SPEED;

    // Обновление позиции с учетом скорости и времени
    mPosX += mVelX * (deltaTime / 1000.0f);
    mPosY += mVelY * (deltaTime / 1000.0f);

    // Ограничение движения точки в пределах экрана
    if (mPosX < 0) mPosX = 0;
    if (mPosX > screenWidth - DOT_SIZE) mPosX = screenWidth - DOT_SIZE;
    if (mPosY < 0) mPosY = 0;
    if (mPosY > screenHeight - DOT_SIZE) mPosY = screenHeight - DOT_SIZE;
}

// Отрисовка точки
void Dot::render(SDL_Renderer* renderer) {
    SDL_Rect fillRect = { static_cast<int>(mPosX), static_cast<int>(mPosY), DOT_SIZE, DOT_SIZE };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // цвет игрока (red)
    SDL_RenderFillRect(renderer, &fillRect);
}
