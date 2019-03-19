#include "Grid.h"

Grid::Grid(bool draw) :
	m_draw(draw)
{
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			m_tiles[std::to_string(j) + "," + std::to_string(i)] = Tile(j * 25, i * 25, 25, 25);
		}
	}

	//Calculate neigbours and populate the vectors of each tile
	//This will make the program much more performant and will avoid
	//having to create and populate vectors for every tile running through astar
	for (auto& tile : m_tiles)
	{
		int x = tile.second.m_gridPosVec.x;
		int y = tile.second.m_gridPosVec.y;

		if (x - 1 >= 0)
		{
			tile.second.neighbours.emplace_back(&m_tiles[std::to_string(x - 1) + "," + std::to_string(y)]);
		}
		if (x + 1 < 40)
		{
			tile.second.neighbours.emplace_back(&m_tiles[std::to_string(x + 1) + "," + std::to_string(y)]);
		}
		if (y - 1 >= 0)
		{
			tile.second.neighbours.emplace_back(&m_tiles[std::to_string(x) + "," + std::to_string(y - 1)]);
		}
		if (y + 1 < 40)
		{
			tile.second.neighbours.emplace_back(&m_tiles[std::to_string(x) + "," + std::to_string(y + 1)]);
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
			tile.second.draw(renderer);
	}
}

double Grid::calculateH(Tile& from, Tile & dest)
{
	double H = (sqrt((from.m_pos.x - dest.m_pos.x)*(from.m_pos.x - dest.m_pos.x)
		+ (from.m_pos.y - dest.m_pos.y)*(from.m_pos.y - dest.m_pos.y)));
	return H;
}
