#ifndef DOT_H
#define DOT_H

#include <SDL2/SDL.h>

class Dot {
public:
    // Конструктор
    Dot(int x, int y);

    // Обработка событий клавиатуры
    void handleEvent(SDL_Event& e, bool* keys);

    // Движение точки
    void move(bool* keys, Uint32 deltaTime, int screenWidth, int screenHeight);

    // Отрисовка точки
    void render(SDL_Renderer* renderer);

    // Геттеры для позиции
    float getX() const { return mPosX; }
    float getY() const { return mPosY; }
	
	float mPosX, mPosY; // позиция точки
    float mVelX, mVelY; // Скорость по осям 

private:

};

#endif
