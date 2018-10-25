#pragma once
#include "RenderComponent.h"
#include "PositionComponent.h"
#include "HealthComponent.h"
#include "SDL.h"
#include <vector>
#include <iostream>
#include "Entity.h"

class RenderSystem
{
	std::vector<Entity*> entities;

public:
	void addEntity(Entity& e) { entities.push_back(&e); };
	void setWindow(SDL_Surface& w) { m_surface = &w; }
	void draw()
	{
		for (auto& e : entities)
		{
			if (e->getAlive()) //Only draw the entity if their health is greater than 0
			{
				auto *hpComp = dynamic_cast<HealthComponent*>(&e->getComponent("HealthComp"));
				auto *rendComp = dynamic_cast<RenderComponent*>(&e->getComponent("RenderComp"));
				auto *posComp = dynamic_cast<PositionComponent*>(&e->getComponent("PositionComp"));
				rendComp->setRect(posComp->getPosition().first, posComp->getPosition().second, rendComp->getRec()->w, rendComp->getRec()->h);
				auto col = SDL_MapRGB(m_surface->format, rendComp->getColor().r, rendComp->getColor().g, rendComp->getColor().b);
				SDL_FillRect(m_surface, rendComp->getRec(), col); //Draw the entities square
			}
		}
	}
private:
	SDL_Surface * m_surface;
};