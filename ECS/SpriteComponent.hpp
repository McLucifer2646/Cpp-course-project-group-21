#pragma once

#include "Components.hpp"
#include "SDL2/SDL.h"
#include "../TextureManager.hpp"

class SpriteComponent : public Component
{
    private:
        TransformComponent *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

    public:
        SpriteComponent() = default;
        SpriteComponent(const char* path)//, int srcw, int srch)
        {
            setTex(path);
            //setBounds(srcw, srch);
        }

        ~SpriteComponent()
        {
            SDL_DestroyTexture(texture);
        }

        void setTex(const char* path)
        {
            texture = TextureManager::LoadTexture(path);
        }

        // void setBounds(int srcw, int srch)
        // {
        //     srcRect.w = srcw;
        //     srcRect.h = srch;
        // }

        void init() override 
        {
            transform = &entity->getComponent<TransformComponent>();

            srcRect.x = srcRect.y = 0;
            srcRect.w = transform->width;
            srcRect.h = transform->height;            
            
        }
        void update() override 
        {
            destRect.x = static_cast<int>(transform->position.x);
            destRect.y = static_cast<int>(transform->position.y);
            destRect.w = static_cast<int>(transform->width * transform->scale);
            destRect.h = static_cast<int>(transform->height * transform->scale);
        }
        void draw() override 
        {
            TextureManager::Draw(texture, srcRect, destRect);
        }
};