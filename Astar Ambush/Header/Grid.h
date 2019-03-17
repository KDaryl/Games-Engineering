#pragma once
#include "SDL.h"
#include "Tile.h"
#include <vector>

//40 Tiles - 25x25 tile size

class Grid
{
public:
	Grid(bool draw);
	void update(double dt);
	void draw(SDL_Renderer* renderer);

	//Set draw
	void setDraw(bool b) { m_draw = b; }
	//Get Draw
	bool getDraw() { return m_draw; }
private:
	bool m_draw;
	std::vector<Tile*> m_tiles;
};