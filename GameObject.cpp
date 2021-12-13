#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
    // renderer = ren;
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}

void GameObject::update()
{
    //xpos++;
    //ypos++;

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.h = 128;
    destRect.w = 60;    

}

void GameObject::render()
{
    SDL_RenderCopy(Game::renderer, objTexture, NULL, &destRect);
}