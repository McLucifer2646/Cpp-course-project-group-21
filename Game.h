#pragma once
#include<SDL.h>
#include<SDL_mixer.h>
#include<SDL_image.h>
#include<iostream>
#include<vector>
using namespace std;

class ColliderComponent;

class Game
{
public:

	Game();
	~Game();

	void init(const char *title, int h, int w, int x, int y, bool fscreen);

	void handleEvent();
	void clean();
	void render();
	void update();

	bool running();

	enum groupLabel : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupBullets
	};

	static SDL_Renderer* ren;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static int lt;
	static int hs;

private:
	SDL_Window *win;

};