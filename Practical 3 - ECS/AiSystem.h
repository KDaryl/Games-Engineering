#pragma once
#include "PositionComponent.h"
#include <iostream>
#include "Entity.h"

class AiSystem
{
	std::vector<Entity*> entities;

public:
	AiSystem() : goLeft(true) {}
	void addEntity(Entity& e) { entities.push_back(&e); };
	void update(int maxW)
	{
		for (auto& e : entities)
		{
			auto *posComp = dynamic_cast<PositionComponent*>(&e->getComponent("PositionComp"));
			auto pos = posComp->getPosition();

			if (goLeft)
			{
				pos.first -= 2.f;

				if (pos.first <= 0)
					goLeft = false;
			}
			else
			{
				pos.first += 2.f;

				if (pos.first + 50 >= maxW)
					goLeft = true;
			}

			posComp->setPosition(pos);

		}

	}
private:
	bool goLeft;
};