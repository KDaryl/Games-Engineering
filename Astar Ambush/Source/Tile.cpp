#include "Tile.h"

Tile::Tile(int x, int y, int w, int h) :
	m_rect({ x, y, w, h }),
	m_pos(x, y),
	m_gridPosVec(x / 25, y / 25),
	m_gridPos(std::to_string(x / 25) + "," + std::to_string(y / 25)),
	gCost(0),
	hCost(0),
	fCost(0),
	visited(false),
	m_isObstacle(false),
	closed(false),
	spotTaken(false)
{
	m_color = { 255, 255, 255, 255 };
}

void Tile::update(double dt)
{
}

void Tile::draw(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, m_color.x, m_color.y, m_color.w, m_color.h);
	if (m_isObstacle)
	{
		SDL_RenderFillRect(renderer, &m_rect);
		//Draw line through wall to show drawing of lines?
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawLine(renderer, m_pos.x + 12.5f, m_pos.y, m_pos.x + 12.5f, m_pos.y + 25);
	}
	else
		SDL_RenderDrawRect(renderer, &m_rect);
}

void Tile::setObstacle(bool b)
{
	m_isObstacle = b;
	if (!b)
		m_color = { 255, 255, 255, 255 }; //White
	else
	{
		m_color = { 255, 175, 65, 255 }; //Orange
		spotTaken = true;
	}

}
