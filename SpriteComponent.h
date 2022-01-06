#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srect, drect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteflip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	SpriteComponent(const char* path, int idle_id, int idle_f, int walk_id, int walk_f, int att_id, int att_f, int dead_id, int dead_f, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(idle_id, idle_f, 100);
		Animation walk_p = Animation(walk_id, walk_f, 100);
		Animation walk_a = Animation(att_id, att_f, 100);
		Animation dead = Animation(dead_id, dead_f, 100);


		//Animation walk_a = Animation(1, 12, 100);
		//Animation dead = Animation(2, 15, 100);
		//Animation idle = Animation(3, 12, 100);
		//Animation walk_p = Animation(4, 18, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk&peace", walk_p);
		animations.emplace("Walk&attack", walk_a);
		animations.emplace("dead", dead);
		

		play("Idle");
		
		setText(path);
	}

	SpriteComponent(const char* path)
	{
		setText(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setText(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srect.x = srect.y = 0;
		srect.w = transform->width;
		srect.h = transform->height;

	}

	void update() override
	{
		if (animated)
		{
			srect.x = srect.w * static_cast<int>((SDL_GetTicks() / speed)%frames);
		}

		srect.y = animIndex * transform->height;


		drect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		drect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		drect.w = transform->width * transform->scale;
		drect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::draw(texture, srect, drect,spriteflip);
	}

	void play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

};