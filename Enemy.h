#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include "Dot.h" // Для доступа к позиции игрока
#include "constants.h"

class Enemy {
public:
    Enemy(int x, int y);
    void updatePosition(const Dot& player, Uint32 deltaTime, int screenWidth, int screenHeight);
    void render(SDL_Renderer* renderer) const;
	
    float getX() const { return mPosX; }
    float getY() const { return mPosY; }


private:
	float mPosX, mPosY; // Текущая позиция врага
};

#endif
