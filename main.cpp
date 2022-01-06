#include<iostream>
#include"Game.h"

int main(int argc, char* argv[])
{

	Game* game = new Game();

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 framestart;
	int frameTime;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	Mix_Music* bgm = Mix_LoadMUS("The-Beginning-w-Caturday.mp3");



	game->init("NewGame", 640, 800, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0);
	Mix_PlayMusic(bgm, -1);
	while (game->running())
	{

		framestart = SDL_GetTicks();

		game->handleEvent();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - framestart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}

	}

	game->clean();
	Mix_FreeMusic(bgm);
	Mix_CloseAudio();
	return 0;
}
