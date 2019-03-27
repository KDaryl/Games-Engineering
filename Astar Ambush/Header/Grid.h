#pragma once
#include "SDL.h"
#include "Tile.h"
#include <vector>
#include <map> >

//40 Tiles - 25x25 tile size

class Grid
{
public:
	Grid(bool draw);
	void update(double dt);
	void draw(SDL_Renderer* renderer);
	void resetSpotsBools();

	void setResetSpotsTaken(bool b);

	static double calculateH(Tile& from, Tile& dest);

	//Set draw
	void setDraw(bool b) { m_draw = b; }
	//Get Draw
	bool getDraw() { return m_draw; }
	bool toReset() { return m_resetSpotsTaken; }

	std::map<std::string, Tile> m_tiles;
private:
	bool m_draw, m_resetSpotsTaken;
};