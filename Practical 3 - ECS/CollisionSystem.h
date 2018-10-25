#pragma once
#include "HealthComponent.h"
#include <iostream>
#include <string> //Allows for << operator
#include "Entity.h"

class CollisionSystem
{
	std::vector<Entity*> entities;

public:
	void addEntity(Entity& e) { entities.push_back(&e); };
	bool collided(SDL_Rect* a, SDL_Rect* b) //Simple rectangular collision
	{
		if (a->x < b->x + b->w &&
			a->x + a->w > b->x &&
			a->y < b->y + b->h &&
			a->h + a->y > b->y) {
			return true;
		}
		return false;
	}
	void handleCollisions() //Handles collisions between entities
	{
		for (auto& aE : entities) //Loop through all entites with a control system
		{
			if (aE->getName() == "Player")
			{
				//Loop through all entities again
				for (auto& bE : entities)
				{
					if (bE->getAlive() && bE->getName() != "Player") //Check for collisions with player apart from with itself
					{
						auto *pRcomp = dynamic_cast<RenderComponent*>(&aE->getComponent("RenderComp")); //Player
						auto *bRcomp = dynamic_cast<RenderComponent*>(&bE->getComponent("RenderComp")); //Other collidable entity
						auto *bHcomp = dynamic_cast<HealthComponent*>(&bE->getComponent("HealthComp")); //Other collidable entities HP

						if (collided(pRcomp->getRec(), bRcomp->getRec()))
						{
							std::cout << "Player is colliding with " << bE->getName() << std::endl;
							bHcomp->setHealth(bHcomp->getHealth() - 1);
							if (bHcomp->getHealth() <= 0)
								bE->setAlive(false);
							std::cout << bE->getName() << "'s new Health is now : " << bHcomp->getHealth() << std::endl;
						}
					}
				}


				break;//Break when collision checking is done
			}
		}
	}
};