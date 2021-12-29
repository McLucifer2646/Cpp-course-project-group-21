#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <vector>

using namespace std;

class ColliderComponent;

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

        static SDL_Renderer *renderer;
        static SDL_Event event;
        static vector<ColliderComponent*> colliders;

    private:
        int count = 0;
        bool isRunning;
        SDL_Window *window;
        //SDL_Renderer *renderer;
};

#endif