#pragma once

#include "Components.hpp"
#include "SDL2/SDL.h"

class SpriteComponent : public Component
{
    private:
        TransformComponent *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

    public:
        SpriteComponent() = default;
        SpriteComponent(const char* path, int srcw, int srch)
        {
            setTex(path);
            setBounds(srcw, srch);
        }

        void setTex(const char* path)
        {
            texture = TextureManager::LoadTexture(path);
        }

        void setBounds(int srcw, int srch)
        {
            srcRect.w = srcw;
            srcRect.h = srch;
        }

        void init() override 
        {
            transform = &entity->getComponent<TransformComponent>();

            srcRect.x = srcRect.y = 0;
            
            destRect.w = 110;
            destRect.h = 256;
        }
        void update() override 
        {
            destRect.x = transform->x();
            destRect.y = transform->y();
        }
        void draw() override 
        {
            TextureManager::Draw(texture, srcRect, destRect);
        }
}