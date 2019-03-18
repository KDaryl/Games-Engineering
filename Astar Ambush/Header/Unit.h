#pragma once
#include "SDL.h"
#include "Vector2f.h"
#include "InputHandler.h"

class Unit
{
public:
	Unit(int x, int y, bool player);

	void update(double dt);
	void draw(SDL_Renderer* renderer);
	void handleInput(InputHandler& input);
private:
	bool m_isPlayer, m_move;
	float m_moveSpeed, m_moveTimer;
	Vector2f m_pos, m_gridPos, m_velocity;
	SDL_Rect m_rect, m_color;
};