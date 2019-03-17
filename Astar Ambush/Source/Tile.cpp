#include "Tile.h"

Tile::Tile(int x, int y, int w, int h) :
	m_rect({ x, y, w, h }),
	m_pos(x, y)
{

}

void Tile::update(double dt)
{
}

void Tile::draw(SDL_Renderer * renderer)
{
	SDL_RenderDrawRect(renderer, &m_rect);
}
