#include "Game.hpp"

SDL_Texture *Bhishma, *back_tex;
SDL_Rect srcR, destR;

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int w, int h, bool fullscrean)
{
    int flag = 0;
    if (fullscrean)
        flag = SDL_WINDOW_FULLSCREEN;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "Initialisation complete" << endl;
        window = SDL_CreateWindow(title, xpos, ypos, w, h, flag);
        if (window)
            cout << "Window created" << endl;

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "Renderer created" << endl;
        }
        isRunning = true;

        SDL_Surface *back_surface = IMG_Load("assets/main.png");
        back_tex = SDL_CreateTextureFromSurface(renderer, back_surface);
        SDL_Surface *temp = IMG_Load("assets/Bhishm.png");
        Bhishma = SDL_CreateTextureFromSurface(renderer, temp);
        SDL_FreeSurface(temp);
        SDL_FreeSurface(back_surface);
    }
    else
        isRunning = false;
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

void Game::update()
{
    count++;
    destR.h = 200;
    destR.w = 80;
    destR.y = 150;
    destR.x = 20;
}

void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, back_tex, NULL, NULL);
    SDL_RenderCopy(renderer, Bhishma, NULL, &destR);
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game Cleaned" << endl;
}