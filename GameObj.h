#pragma once

#include "Game.h"

class GameObject
{
public:
	GameObject(const char* textSheet);
	~GameObject();

	void Update(int x, int y, int h, int w);
	void Render();

	void set_xpos(int x) { xpos = x; }
	void set_ypos(int y) { ypos = y; }
	int get_xpos() { return xpos; }
	int get_ypos() { return ypos; }
	int get_velocity() { return vel; }
	void set_velocity(int v) { vel = v; }

	void MoveObj(int x_vel, int y_vel);

private:
	int xpos;
	int ypos;
	int vel;

	SDL_Texture* objText;
	SDL_Rect srect, drect;

	SDL_Renderer* ren2;
};