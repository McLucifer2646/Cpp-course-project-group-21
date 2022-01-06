#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fname)
{
	SDL_Surface* tmps = IMG_Load(fname);
	SDL_Texture* text = SDL_CreateTextureFromSurface(Game::ren, tmps);

	SDL_FreeSurface(tmps);

	return text;
}

void TextureManager::draw(SDL_Texture* text, SDL_Rect srect, SDL_Rect drect, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::ren, text, &srect, &drect,NULL,NULL,flip);
}