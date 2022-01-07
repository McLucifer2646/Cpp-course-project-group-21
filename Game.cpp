#include "Game.h"
#include "TextureManager.h"
#include "GameObj.h"
#include "Map.h"

#include<time.h>

#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

Game::Game(){}
Game::~Game(){}

GameObject* gsf1;
GameObject* gsf2;
GameObject* es1;
GameObject* es2;
GameObject* gbg1;
GameObject* gbg2;
GameObject* cbg1;
GameObject* p1;
GameObject* p2;
GameObject* p3;
GameObject* bullet;
GameObject* bullets[3];
GameObject* lw;
GameObject* rs1;
GameObject* rs2;
GameObject* e1;
GameObject* e2;
GameObject* e2e;

Map* map1;

Manager manager;
auto& player(manager.addEntity());
auto& enemy(manager.addEntity());
//auto& wall(manager.addEntity());

//auto& enemies(manager.getGroup(groupEnemies));

const char* pla1;
const char* pla2;
const char* pla3; 
//auto& tile0(manager.addEntity());
//auto& tile1(manager.addEntity());
//auto& tile2(manager.addEntity());

SDL_Renderer* Game::ren = nullptr;
SDL_Event Game::event;
bool Game::isRunning = false;
SDL_Rect Game::camera = { 0,0,800,640 };

SDL_Surface* icon = IMG_Load("game_icon.png");

int score = 3;
int sm = 0;
int bulletFlag = 0;
int Game::hs = 1;
int Game::lt = 0;

float cnt = 0;
void Game::init(const char * tit, int h, int w, int x, int y, bool f)
{
	int fl = 0;
	if (f == true)
		fl = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		win = SDL_CreateWindow(tit, x, y, w, h, fl);
		SDL_SetWindowIcon(win, icon);
		if (win)
			cout << "Window created\n";

		ren = SDL_CreateRenderer(win, -1, 0);
		if (ren)
		{
			SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
			cout << "Renderer created\n";
		}

		isRunning = true;
	}

	else
		isRunning = false;

	
	gsf1 = new GameObject("startf1.png");
	gsf2 = new GameObject("startf2.png");

	es1 = new GameObject("es1.png");
	es2 = new GameObject("es2.png");

	gbg1 = new GameObject("homebg.png");
	gbg2 = new GameObject("gunner.png");
	cbg1 = new GameObject("bg2.png");

	p1 = new GameObject("a1.png");
	p2 = new GameObject("a2.png");
	p3 = new GameObject("a3.png");

	bullet = new GameObject("bullet.png");
	for (int b = 0; b < 3; b++)
	{
		bullets[b] = new GameObject("bullet.png");
		bullets[b]->Update(b * 100 + 30, 05, 50, 50);
	}

	lw = new GameObject("loss.png");

	rs1 = new GameObject("rs1.png");
	rs2 = new GameObject("rs2.png");

	e1 = new GameObject("e1.png");
	e2 = new GameObject("e2.png");

	e2e = new GameObject("e2e.png");

	map1 = new Map("Map_ss.png",2,32);
	
	//ecs implementation
	
	//tile0.addComponent<TileComponent>(440, 30, 20, 20, 2);
	//tile0.addComponent<ColliderComponent>("grass");
	//tile1.addComponent<TileComponent>(440, 100, 20, 20, 1);
	//tile1.addComponent<ColliderComponent>("dirt");
	//tile2.addComponent<TileComponent>(440, 500, 20, 20, 0);
	//tile2.addComponent<ColliderComponent>("water");

	map1->loadMap("Map_matrix.map", 25, 20);
	//player.addComponent<TransformComponent>(100, 300, 480, 500, 2);
	

	enemy.addComponent<TransformComponent>(900, 300, 135, 153, 1);
	enemy.addComponent<SpriteComponent>("villain.png", 0, 12, 0, 12, 0, 12, 0, 12, true);
	enemy.addGroup(groupPlayers);

	//wall.addComponent<TransformComponent>(440.0f, 150.0f, 600, 20, 1);
	//wall.addComponent<SpriteComponent>("dirt.png");
	//wall.addComponent<ColliderComponent>("wall");
	//wall.addGroup(groupMap);
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

void Game::handleEvent()
{
	SDL_PollEvent(&event);
	int x = (rand() % (1200 - 300 + 1)) + 300;
	int y = (rand() % (900 - 300 + 1)) + 300;

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_KEYDOWN:
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_SPACE:
			if (hs == 0)
			{
				if (bulletFlag == 0)
				{
					if (lt == 0)
					{
						bullet->set_xpos(player.getComponent<TransformComponent>().position.x + 110 - camera.x);
						bullet->set_ypos(player.getComponent<TransformComponent>().position.y + 70 + camera.y);
						bulletFlag = 1;
						sm = 1;
					}

					else
					{
						bullet->set_xpos(player.getComponent<TransformComponent>().position.x - camera.x);
						bullet->set_ypos(player.getComponent<TransformComponent>().position.y + 70 + camera.y);
						bulletFlag = 1;
						sm = 1;
					}
				}
			}
			break;

		default:
			break;
		}
	default:
		break;
	}
	if (hs == 0)
	{
		if (bullet->get_xpos() - enemy.getComponent<TransformComponent>().position.x <= camera.x)
		{
			if ((player.getComponent<TransformComponent>().position.y - enemy.getComponent<TransformComponent>().position.y) <= 40 && sm == 1)
			{
				if (lt == 0)
				{
					if (abs(bullet->get_xpos() - enemy.getComponent<TransformComponent>().position.x + camera.x) <= 10)
					{
						std::cout << "x-match" << bullet->get_xpos() << enemy.getComponent<TransformComponent>().position.x << camera.x << "\n";
						sm = 0;
						bulletFlag = 0;
						enemy.getComponent<TransformComponent>().position.x = x;
						enemy.getComponent<TransformComponent>().position.y = y;
					}
				}

				else
				{
					if (abs(bullet->get_xpos() - enemy.getComponent<TransformComponent>().position.x + camera.x-60) <= 10)
					{
						std::cout << "x-match" << bullet->get_xpos() << enemy.getComponent<TransformComponent>().position.x << camera.x << "\n";
						sm = 0;
						bulletFlag = 0;
						enemy.getComponent<TransformComponent>().position.x = x;
						enemy.getComponent<TransformComponent>().position.y = y;
					}
				}
			}
		}
	}
}

void Game::update()
{
	gbg1->Update(0, 0, -1, -1);

	gsf1->Update(220+20, 200, 85, 85);
	gsf2->Update(220+20, 200, 85, 85);


	if (hs==1)
	{
		gbg2->Update(400, 200, 300, 300);
		es1->Update(220 + 20, 400, 85, 85);
		es2->Update(220 + 20, 400, 85, 85);
	}

	else if (hs == 2)
	{
		cbg1->Update(0, 0, -1, -1);
		p1->Update(40, 200, 150, 150);
		p2->Update(315, 200, 150, 150);
		p3->Update(590, 200, 150, 150);
	}

	else if (hs == 3)
	{
		lw->Update(0, 0, -1, -1);
		rs1->Update(240, 250, 85, 85);
		rs2->Update(240, 250, 85, 85);
		e1->Update(560, 250, 85, 85);
		e2->Update(560, 250, 85, 85);
	}

	else
	{
		e2e->Update(600, 05, 60, 180);

		if (bulletFlag == 1)
		{
			if (lt == 0)
			{
				bullet->Update(bullet->get_xpos() + 5, player.getComponent<TransformComponent>().position.y + 25 - camera.y, 15, 15);
				if (bullet->get_xpos() >= 800)//if bullet reaches end of screen
				{
					bulletFlag = 0;
					score = score - 1;
					sm = 0;
					if (score == 0)
					{
						hs = 3;
					}

					bullet->Update(player.getComponent<TransformComponent>().position.x + 110 - camera.x, player.getComponent<TransformComponent>().position.y + 70 - camera.y, 15, 15);
				}
			}

			else
			{
				bullet->Update(bullet->get_xpos() - 5, player.getComponent<TransformComponent>().position.y + 25 - camera.y, 15, 15);
				if (bullet->get_xpos() <= 0)//if bullet reaches end of screen
				{
					bulletFlag = 0; score = score - 1;
					sm = 0;
					if (score == 0)
					{
						hs = 3;
					}
					bullet->Update(player.getComponent<TransformComponent>().position.x + 110 - camera.x, player.getComponent<TransformComponent>().position.y + 70 - camera.y, 15, 15);
				}
			}
		}
		else
		{
			bullet->Update(player.getComponent<TransformComponent>().position.x + 1100-camera.x, player.getComponent<TransformComponent>().position.y + 70-camera.y, 15, 15);
		}

		gbg2->Update(50+20, 300, 300, 200);

		SDL_Rect playercol = player.getComponent<ColliderComponent>().collider;
		Vector2D playerpos = player.getComponent<TransformComponent>().position;

		manager.refresh();
		manager.update();
		
		for (auto& c : colliders)
		{
			SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
			if (Collision::AABB(cCol, playercol))
			{
				player.getComponent<TransformComponent>().position = playerpos;
			}
		}

		camera.x = player.getComponent<TransformComponent>().position.x - 400;
		camera.y = player.getComponent<TransformComponent>().position.y - 320;

		if (camera.x < 0)
			camera.x = 0;

		if (camera.y < 0)
			camera.y = 0;


		if (camera.x > camera.w)
			camera.x = camera.w;

		if (camera.y > camera.h)
			camera.y = camera.h;
	}
}

void Game::render()
{
	int x, y;
	Uint32 button = SDL_GetMouseState(&x, &y);
	SDL_RenderClear(ren);

	if (hs==1)
	{
		gbg1->Render();
		if (x >= 220+20 && x <= (220+20 + 85) && y >= 200 && y <= (200 + 85))
		{
			if ((button & SDL_BUTTON_LMASK) != 0)
				hs = 2;
			gsf1->Render();
		}
		else
		{
			gsf2->Render();
		}

		if (x >= 220 + 20 && x <= (220 + 20 + 85) && y >= 400 && y <= (4000 + 85))
		{
			if ((button & SDL_BUTTON_LMASK) != 0)
				isRunning = false;
			es2->Render();
		}
		else
		{
			es1->Render();
		}
		gbg2->Render();
	}

	else if (hs == 2)
	{
		cbg1->Render();
		p1->Render();
		p2->Render();
		p3->Render();

		if (x >= 40 && x <= (40 + 150) && y >= 200 && y <= (200 + 150))
		{
			if ((button & SDL_BUTTON_LMASK) != 0)
			{
				hs = 0;
				pla1 = "hero1.png";

				player.addComponent<TransformComponent>(100, 300, 53, 66, 3);
				player.addComponent<SpriteComponent>(pla1,0,12,1,18,2,12,3,15, true);
				player.addComponent<KeyBoardController>();
				player.addComponent<ColliderComponent>("player");
				player.addGroup(groupPlayers);
			}
		}
		else if (x >= 315 && x <= (315 + 150) && y >= 200 && y <= (200 + 150))
		{
			if ((button & SDL_BUTTON_LMASK) != 0)
			{
				hs = 0;
				pla2 = "hero.png";

				player.addComponent<TransformComponent>(100, 300, 94, 80, 1.5);
				player.addComponent<SpriteComponent>(pla2, 0, 8, 1, 6, 1, 6, 3, 6, true);
				player.addComponent<KeyBoardController>();
				player.addComponent<ColliderComponent>("player");
				player.addGroup(groupPlayers);
			}
		}
		else if (x >= 590 && x <= (590 + 150) && y >= 200 && y <= (200 + 150))
		{
			if ((button & SDL_BUTTON_LMASK) != 0)
			{
				hs = 0;
				pla3 = "hero3.png";

				player.addComponent<TransformComponent>(100, 300, 48, 48, 3);
				player.addComponent<SpriteComponent>(pla3, 0, 4, 1, 6, 2, 8, 3, 6, true);
				player.addComponent<KeyBoardController>();
				player.addComponent<ColliderComponent>("player");
				player.addGroup(groupPlayers);
			}
		}
	}

	else if (hs == 3)
	{
		player.getComponent<TransformComponent>().position.x = 10000000;
		lw->Render();
		if (x >= 220 + 20 && x <= (220 + 20 + 85) && y >= 250 && y <= (250 + 85))
		{
			if ((button & SDL_BUTTON_LMASK) != 0)
			{
				score = 3;
				hs = 2;
			}
			rs2->Render();
		}
		else
		{
			rs1->Render();
		}

		if (x >= 540 + 20 && x <= (540 + 20 + 85) && y >= 250 && y <= (250 + 85))
		{
			if ((button & SDL_BUTTON_LMASK) != 0)
			{
				isRunning = false;
			}
			e2->Render();
		}
		else
		{
			e1->Render();
		}
	}
	else
	{
		gbg1->Render();
		gbg2->Render();

		for (auto& t : tiles)
		{
			t->draw();
		}

		for (auto& c : colliders)
		{
			c->draw();
		}
		bullet->Render();

		for (auto& p : players)
		{
			p->draw();
		}

		for (int b = 0; b < score; b++)
		{
			bullets[b]->Render();
		}

		e2e->Render();

	}
	SDL_RenderPresent(ren);
}

bool Game::running()
{
	return isRunning;
}

void Game::clean()
{
	SDL_FreeSurface(icon);
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	SDL_Quit();
	cout << "Game Quit\n";
}