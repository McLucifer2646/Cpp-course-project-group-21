#pragma once

#include "Components.hpp"
#include "SDL2/SDL.h"

class SpriteComponent : public Component
{
    private:
        TransformComponent *position;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

    public:
        SpriteComponent() = default;
        SpriteComponent(const char* path)
        {
            setTex(path);
        }

        void setTex(const char* path)
        {
            texture = TextureManager::LoadTexture(path);
        }

        void init() override 
        {
            position = &entity->getComponent<PositionComponent>();

            srcRect.x = srcRect.y = 0;
            srcRect.w = 312;
            srcRect.h = 800;
            destRect.w = 110;
            destRect.h = 256;
        }
        void update() override 
        {
            destRect.x = position->x();
            destRect.y = position->y();
        }
        void draw() override 
        {
            TextureManager::Draw(texture, srcRect, destRect);
        }
}