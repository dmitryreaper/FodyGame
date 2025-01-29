// Dot.cpp
#include "Dot.h"
#include <iostream>

const int DOT_SIZE = 20;

Dot::Dot(int x, int y) : mPosX(x), mPosY(y) {}

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

void Dot::move(bool* keys, Uint32 deltaTime, int screenWidth, int screenHeight) {
    // Умножаем перемещение на время, прошедшее с последнего кадра
    if (keys[0]) mPosY -= DOT_SIZE * (deltaTime / 100.0); // W
    if (keys[1]) mPosY += DOT_SIZE * (deltaTime / 100.0); // S
    if (keys[2]) mPosX -= DOT_SIZE * (deltaTime / 100.0); // A
    if (keys[3]) mPosX += DOT_SIZE * (deltaTime / 100.0); // D

    // Ограничение движения точки в пределах экрана
    if (mPosX < 0) mPosX = 0;
    if (mPosX > screenWidth - DOT_SIZE) mPosX = screenWidth - DOT_SIZE;
    if (mPosY < 0) mPosY = 0;
    if (mPosY > screenHeight - DOT_SIZE) mPosY = screenHeight - DOT_SIZE;
}

void Dot::render(SDL_Renderer* renderer) {
    SDL_Rect fillRect = { static_cast<int>(mPosX), static_cast<int>(mPosY), DOT_SIZE, DOT_SIZE };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &fillRect);
}
