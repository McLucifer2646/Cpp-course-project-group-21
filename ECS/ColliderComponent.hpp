#pragma once
#include <string>
#include "SDL2/SDL.h"
#include "ECS.hpp"

class ColliderComponent : public Component
{
	SDL_Rect collider;
	std::string tag;

	TransformComponent* transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	void init() override
	{
		if(!entity->hasComponent<TransformComponent>())
		{
			entity->addcomponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = static_cast<int>(transform->width * transform->scale);
		collider.h = static_cast<int>(transform->height * transform->scale);
	}
}