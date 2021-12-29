#include "Game.hpp"
#include "TextureManager.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

//#include "ECS/ECS.hpp"
// #include "Components.hpp"


SDL_Texture *back_tex;

SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;

std::vector<ColliderComponent*> Game::colliders;

Manager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

// SDL_Texture *player, *back_tex;
// SDL_Rect srcR, destR;

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

        // //  SDL_Surface *back_surface = IMG_Load("assets/main.png");
        //back_tex =  TextureManager::LoadTexture("assets/main.png");
        // // // SDL_Surface *temp = IMG_Load("assets/Bhishm.png");
        // player = TextureManager::LoadTexture("assets/Bhishm.png", renderer);
        // // //SDL_FreeSurface(temp);
        // //  SDL_FreeSurface(back_surface);        
        //back_tex = new GameObject("assets/main.png", renderer);

        //player = new GameObject("assets/Bhishm.png", 4, 300);

        player.addComponent<TransformComponent>(4, 300, 94, 80, 2.5);
        player.addComponent<SpriteComponent>("assets/hero.png", 8, 100);//, 312, 800);
        player.addComponent<KeyboardController>();
        player.addComponent<ColliderComponent>("player");

        wall.addComponent<TransformComponent>(600, 300, 800, 312, 0.35);
        wall.addComponent<SpriteComponent>("assets/Bhishm.png");
        wall.addComponent<ColliderComponent>("wall");


    }
    else
        isRunning = false;
}

void Game::handleEvents()
{
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
    //count++;
    //player->update();
    manager.refresh();
    manager.update();
    
    if(Collision::AABB(player.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider))
    {
        player.getComponent<TransformComponent>().velocity * -1;
        std::cout << "Wall Hit" << std::endl;
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    manager.draw();
    //SDL_RenderCopy(renderer, back_tex, NULL, NULL);
    //player->render(); 
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game Cleaned" << endl;
}
