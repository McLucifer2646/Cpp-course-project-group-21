#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyBoardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		
		if (Game::event.type == SDL_KEYDOWN)
		{ 
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				sprite->play("Walk&peace");
				transform->velocity.y = -1;
				break;

			case SDLK_s:
				transform->velocity.y = 1;
				sprite->play("Walk&peace");
				break;

			case SDLK_a:
				transform->velocity.x = -1;
				sprite->play("Walk&peace");
				Game::lt = 1;
				sprite->spriteflip = SDL_FLIP_HORIZONTAL;
				break;

			case SDLK_d:
				transform->velocity.x = 1;
				sprite->play("Walk&peace");
				Game::lt = 0;
				sprite->spriteflip = SDL_FLIP_NONE;
				break;
			
			case SDLK_SPACE:
				sprite->play("Walk&attack");
				break;

			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->play("Idle");
				break;

			case SDLK_s:
				transform->velocity.y = 0;
				sprite->play("Idle");
				break;

			case SDLK_a:
				transform->velocity.x = 0;
				sprite->play("Idle");
				Game::lt = 1;
				sprite->spriteflip = SDL_FLIP_HORIZONTAL;
				break;

			case SDLK_d:
				transform->velocity.x = 0;
				sprite->play("Idle");
				Game::lt = 0;
				sprite->spriteflip = SDL_FLIP_NONE;
				break;

			case SDLK_ESCAPE:
				Game::hs = 3;
				break;

			case SDLK_SPACE:
				sprite->play("Idle");
				break;


			default:
				break;
			}

		}
	}
};
