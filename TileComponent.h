#pragma once

#include "ECS.h"
#include "SDL.h"

class TileComponent : public Component
{
public:

    SDL_Texture* texture;
    SDL_Rect srect, drect;
    Vector2D position;

    TileComponent() = default;

    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }

    TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, const char* path)
    {
        texture = TextureManager::LoadTexture(path);

        position.x = xpos;
        position.y = ypos;

        srect.x = srcX;
        srect.y = srcY;
        srect.w = tsize;
        srect.h = tsize;

        drect.x = xpos;
        drect.y = ypos;
        drect.w = tsize * tscale;
        drect.h = tsize * tscale;

    }

    void update() override
    {
        drect.x = position.x - Game::camera.x;
        drect.y = position.y - Game::camera.y;
    }

    void draw() override
    {
        TextureManager::draw(texture, srect, drect, SDL_FLIP_NONE);
    }
};