#pragma once

#include "Components.hpp"
#include "SDL2/SDL.h"
#include "../TextureManager.hpp"
#include "Animation.hpp"
#include <map>

class SpriteComponent : public Component
{
    private:
        TransformComponent *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

        bool animated = false;
        int frames = 0;
        int speed = 100;

    public:
        int animIndex = 0;

        std::map<const char*, Animation> animations;

        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        SpriteComponent() = default;
        SpriteComponent(const char* path)
        {
            setTex(path);
        }

        SpriteComponent(const char* path, bool isAnimated)
        {
            animated = isAnimated;

            Animation idle = Animation(0, 8, 100);
            Animation walk_p = Animation(1, 6, 100);
            Animation walk_a = Animation(2, 6, 100);

            animations.emplace("Idle", idle);
            animations.emplace("Walk&peace", walk_p);
            animations.emplace("Walk&attack", walk_a);

            Play("Idle");
            setTex(path);
        }

        ~SpriteComponent()
        {
            SDL_DestroyTexture(texture);
        }

        void setTex(const char* path)
        {
            texture = TextureManager::LoadTexture(path);
        }

        void init() override 
        {
            transform = &entity->getComponent<TransformComponent>();

            srcRect.x = srcRect.y = 0;
            srcRect.w = transform->width;
            srcRect.h = transform->height;            
            
        }
        void update() override 
        {
            if(animated){
                srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
            }

            srcRect.y = animIndex * transform->height;

            destRect.x = static_cast<int>(transform->position.x);
            destRect.y = static_cast<int>(transform->position.y);
            destRect.w = static_cast<int>(transform->width * transform->scale);
            destRect.h = static_cast<int>(transform->height * transform->scale);
        }
        void draw() override 
        {
            TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
        }

        void Play(const char* animName)
        {
            frames = animations[animName].frames;
            speed = animations[animName].speed;
            animIndex = animations[animName].index;
        }
};