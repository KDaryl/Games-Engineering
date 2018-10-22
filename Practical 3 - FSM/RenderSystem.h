#pragma once
#include "RenderComponent.h"
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
		std::cout << "RenderSystem Update" << std::endl;

		for (auto& e : entities)
		{
			auto *rendComp = dynamic_cast<RenderComponent*>(&e->getComponent("RenderComp"));
			auto col = SDL_MapRGB(m_surface->format, rendComp->getColor().r, rendComp->getColor().g, rendComp->getColor().b);
			SDL_FillRect(m_surface, rendComp->getRec(), col); //Draw the entities square
		}
	}
private:
	SDL_Surface * m_surface;
};