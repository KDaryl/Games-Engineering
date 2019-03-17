#include "Grid.h"

Grid::Grid(bool draw) :
	m_draw(draw)
{
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			m_tiles.push_back(new Tile(j * 25, i * 25, 25, 25));
		}
	}
}

void Grid::update(double dt)
{
}

void Grid::draw(SDL_Renderer * renderer)
{
	if (m_draw)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

		for (auto& tile : m_tiles)
			tile->draw(renderer);
	}
}
