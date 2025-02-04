#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include "Dot.h" // Для доступа к позиции игрока

class Enemy {
public:
    Enemy(int x, int y);
    void updatePosition(const Dot& player, Uint32 deltaTime, int screenWidth, int screenHeight);
    void render(SDL_Renderer* renderer) const;
    float getX() const { return mPosX; }
    float getY() const { return mPosY; }
    void setX(float x) { mPosX = x; }
    void setY(float y) { mPosY = y; }

private:
    float mPosX, mPosY; // Текущая позиция врага
	const float SPEED = 100.0f;
};

#endif
