#pragma once
#include "PositionComponent.h"
#include <iostream>
#include "Entity.h"

class ControlSystem
{
	std::vector<Entity*> entities;

public:
	void addEntity(Entity& e) { entities.push_back(&e); };
	void handleInput(SDL_Event& e)
	{
		for (auto& ent : entities) //Loop through all entites with a control system
		{
			auto * eComp = dynamic_cast<PositionComponent*>(&ent->getComponent("PositionComp"));
			auto ePos = eComp->getPosition();

			//Check which keys are pressed
			if (e.key.keysym.sym == SDLK_w)
				ePos.second -= 4;
			if (e.key.keysym.sym == SDLK_s)
				ePos.second += 4;
			if (e.key.keysym.sym == SDLK_a)
				ePos.first -= 4;
			if (e.key.keysym.sym == SDLK_d)
				ePos.first += 4;

			eComp->setPosition(ePos.first, ePos.second);
		}
	}
};