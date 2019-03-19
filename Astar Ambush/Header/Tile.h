#pragma once
#include "SDL.h"
#include "Vector2f.h"

class Tile
{
public:
	Tile() {}
	Tile(int x, int y, int w, int h);
	void update(double dt);
	void draw(SDL_Renderer* renderer);
	void setObstacle(bool b) { m_isObstacle = b; }
	//Getters
	std::string gridPos() { return m_gridPos; }
	Tile* previous;
	float gCost, hCost, fCost;
	bool visited;
	Vector2f m_pos, m_gridPosVec;
	bool m_isObstacle;
private:

	SDL_Rect m_rect;
	std::string m_gridPos;
};