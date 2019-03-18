#pragma once
#include "SDL.h"
#include "Vector2f.h"

class Tile
{
public:
	Tile(int x, int y, int w, int h);
	void update(double dt);
	void draw(SDL_Renderer* renderer);

	void setObstacle(bool b) { m_isObstacle = b; }

	//Getters
	Vector2f gridPos() { return m_gridPos; }
private:
	SDL_Rect m_rect;
	Vector2f m_pos, m_gridPos;
	bool m_isObstacle;
};