#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int DOT_SIZE = 20;

class Dot {
public:
    Dot(int x, int y) : mPosX(x), mPosY(y) {}

    void handleEvent(SDL_Event& e) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            switch (e.key.keysym.sym) {
                case SDLK_w: mPosY -= DOT_SIZE; break;
                case SDLK_s: mPosY += DOT_SIZE; break;
                case SDLK_a: mPosX -= DOT_SIZE; break;
                case SDLK_d: mPosX += DOT_SIZE; break;
            }
        }

        // Ограничение движения точки в пределах экрана
        if (mPosX < 0) mPosX = 0;
        if (mPosX > SCREEN_WIDTH - DOT_SIZE) mPosX = SCREEN_WIDTH - DOT_SIZE;
        if (mPosY < 0) mPosY = 0;
        if (mPosY > SCREEN_HEIGHT - DOT_SIZE) mPosY = SCREEN_HEIGHT - DOT_SIZE;
    }

    void render(SDL_Renderer* renderer) {
        SDL_Rect fillRect = { mPosX, mPosY, DOT_SIZE, DOT_SIZE };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &fillRect);
    }

private:
    int mPosX, mPosY;
};

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
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

    Dot dot(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else {
                dot.handleEvent(e);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        dot.render(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
