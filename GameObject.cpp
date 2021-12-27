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

    srcRect.h = 800;
    srcRect.w = 312;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.h = 256;
    destRect.w = 110;    

}

void GameObject::render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}