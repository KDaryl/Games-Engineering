#pragma once
#include "SDL.h"
#include "Vector2f.h"
#include "InputHandler.h"
#include "Grid.h"

class Unit
{
public:
	Unit(int x, int y, bool player, Grid& grid, Unit& playerUnit);

	void update(double dt);
	void draw(SDL_Renderer* renderer);
	void handleInput(InputHandler& input);
	std::string gridPos() { return m_gridPos; }

	void setPath(std::vector<Vector2f> path) { m_path = path, m_currentPathPos = m_path.begin(); }
	void setVelocity(int x, int y) { m_velocity = Vector2f(x, y); }
	bool moving() { return m_move; }
	std::string m_prevPlayerPos;
	Unit* playerPtr() { return m_playerPtr; }
	void setCanUpdate(bool b) { m_canUpdate = b; }
private:
	std::vector<Vector2f>::iterator m_currentPathPos;
	std::vector<Vector2f> m_path;
	Unit* m_playerPtr;
	Grid* m_gPtr;
	bool m_isPlayer, m_move, m_canUpdate;
	float m_moveSpeed, m_moveTimer;
	Vector2f m_pos, m_velocity;
	std::string m_gridPos;
	SDL_Rect m_rect, m_color;

};