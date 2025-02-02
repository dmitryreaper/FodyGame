#include "Enemy.h"
#include <cmath>

Enemy::Enemy(int x, int y) : mPosX(x), mPosY(y) {}

void Enemy::updatePosition(const Dot& player, Uint32 deltaTime, int screenWidth, int screenHeight) {
    float playerX = player.mPosX;
    float playerY = player.mPosY;

    // Вычисляем направление движения
    float dx = playerX - mPosX;
    float dy = playerY - mPosY;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance > 0) {
        float speedFactor = SPEED * (deltaTime / 1000.0f); // Учитываем время между кадрами
        mPosX += (dx / distance) * speedFactor;
        mPosY += (dy / distance) * speedFactor;
    }

    // Ограничение движения в пределах экрана
    if (mPosX < 0) mPosX = 0;
    if (mPosX > screenWidth - ENEMY_SIZE) mPosX = screenWidth - ENEMY_SIZE;
    if (mPosY < 0) mPosY = 0;
    if (mPosY > screenHeight - ENEMY_SIZE) mPosY = screenHeight - ENEMY_SIZE;
}

void Enemy::render(SDL_Renderer* renderer) const {
    SDL_Rect fillRect = { static_cast<int>(mPosX), static_cast<int>(mPosY), ENEMY_SIZE, ENEMY_SIZE };
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Синий цвет для врага
    SDL_RenderFillRect(renderer, &fillRect);
}
