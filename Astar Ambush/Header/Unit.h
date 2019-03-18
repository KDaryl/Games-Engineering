#pragma once
#include "SDL.h"
#include "Vector2f.h"
#include "InputHandler.h"
#include "Grid.h"

class Unit
{
public:
	Unit(int x, int y, bool player, Grid& grid);

	void update(double dt);
	void draw(SDL_Renderer* renderer);
	void handleInput(InputHandler& input);
	Vector2f gridPos() { return m_gridPos; }

	void setVelocity(int x, int y) { m_velocity = Vector2f(x, y); }
private:
	Grid* m_gPtr;
	bool m_isPlayer, m_move;
	float m_moveSpeed, m_moveTimer;
	Vector2f m_pos, m_gridPos, m_velocity;
	SDL_Rect m_rect, m_color;
};