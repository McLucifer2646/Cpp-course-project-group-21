//To create maps based on 2d array Think about this later for now we will be having still backgrounding
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