#pragma once
#include "Game.hpp"

class Map
{
    public:
        Map();
        ~Map();

        void LoadMap();
        void DrawMap();
    
    private:
        SDL_Rect src, dest;
        SDL_Texture* dirt;
        SDL_Texture* grass;
        SDL_Texture* water;
        
        int map[20][25];
};