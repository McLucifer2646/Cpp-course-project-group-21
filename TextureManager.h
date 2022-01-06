#pragma once

#include "Game.h"

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fnamme);
	static void draw(SDL_Texture* text, SDL_Rect srect, SDL_Rect drect, SDL_RendererFlip flip);
};