#include "Game.hpp"

Game *g = nullptr;
int main(int argc, const char *argv[])
{
    g = new Game();
    g->init("Mahabharat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 400, false);
    while (g->running())
    {
        g->handleEvents();
        g->update();
        g->render();
    }
    g->clean();
    return 0;
}