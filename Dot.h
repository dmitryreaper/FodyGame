#ifndef DOT_H
#define DOT_H

#include <SDL2/SDL.h>

class Dot {
public:
    Dot(int x, int y);

    void handleEvent(SDL_Event& e, bool* keys);
    void move(bool* keys, Uint32 deltaTime, int screenWidth, int screenHeight);
    void render(SDL_Renderer* renderer);

private:
    float mPosX, mPosY;
};

#endif
