#include "GameObj.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textSheet)
{
	ren2 = Game::ren;
	objText = TextureManager::LoadTexture(textSheet);
}

void GameObject::Update(int x, int y, int h, int w)
{
	xpos = x;
	ypos = y;

	srect.x = 0;
	srect.y = 0;
	srect.h = 640;
	srect.w = 800;

	drect.x = xpos;
	drect.y = ypos;
	drect.h = h;
	drect.w = w;

}

void GameObject::Render()
{
	if (drect.h == -1)
		SDL_RenderCopy(ren2, objText, &srect, NULL);
	else
		SDL_RenderCopy(ren2, objText, NULL, &drect);
}

void GameObject::MoveObj(int x_vel, int y_vel)
{
	xpos += x_vel;
	ypos += y_vel;
}