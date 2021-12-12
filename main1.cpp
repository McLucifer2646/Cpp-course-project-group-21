#include "Game.hpp"

Game *g = nullptr;
int main(int argc, const char *argv[])
{
    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint32 framestart;
    int frameTime;

    g = new Game();
    g->init("Mahabharat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);
    while (g->running())
    {
        framestart = SDL_GetTicks();

        g->handleEvents();
        g->update();
        g->render();

        frameTime = SDL_GetTicks() - framestart;

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    g->clean();
    return 0;
}