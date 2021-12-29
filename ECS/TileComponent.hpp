#pragma once

#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "SDL2/SDL.h"

class TileComponent : public Component
{
    public:
        TransformComponent *transform;
        SpriteComponent *sprite;

        SDL_Rect tileRect;
        int tileID;
        char* path;

        TileComponent() = default;
        TileComponent(int x, int y, int w, int h, int id)
        {
            tileRect.x = x;
            tileRect.y = y;
            tileRect.w = w;
            tileRect.h = h;
            tileID = id;

            // switch(tileID)
            // {

            // }
        }
};