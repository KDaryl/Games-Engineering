#include "Tile.h"

Tile::Tile(int x, int y, int w, int h) :
	m_rect({ x, y, w, h }),
	m_pos(x, y),
	m_gridPos(std::to_string(x / 25) + "," + std::to_string(y / 25))
{

}

void Tile::update(double dt)
{
}

void Tile::draw(SDL_Renderer * renderer)
{
	SDL_RenderDrawRect(renderer, &m_rect);
}
