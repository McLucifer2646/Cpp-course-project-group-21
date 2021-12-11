#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

using namespace std;

class Game

{
    public:
        Game();
        ~Game();
        void init(const char* title, int xpos, int ypos, int w, int h, bool fullscrean);
        void handleEvents();
        void update();
        void render();
        void clean();
    
        bool running() { return isRunning;}

    private:
        int count = 0;
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;
};

#endif