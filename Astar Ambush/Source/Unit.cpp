#include "Unit.h"

Unit::Unit(int x, int y, bool player) :
	m_pos(x, y),
	m_isPlayer(player),
	m_moveSpeed(.05f),
	m_moveTimer(m_moveSpeed),
	m_move(false)
{
	m_rect = { x, y, 25, 25 };

	//Set colour based on our is player boolean
	if (m_isPlayer)
		m_color = {0, 255, 0, 255};
	else
		m_color = { 255, 0, 0, 255 };
}

void Unit::update(double dt)
{
	if (m_isPlayer)
	{
		if (m_move)
		{
			m_moveTimer -= dt;
			std::cout << m_moveTimer << "\n";
			if (m_moveTimer <= 0)
			{
				m_moveTimer = m_moveSpeed;

				//Move the player
				m_pos += m_velocity * 25;

				if (m_pos.x < 0)
					m_pos.x = 0;
				else if (m_pos.x >= 1000)
					m_pos.x = 1000 - 25;
				if (m_pos.y < 0)
					m_pos.y = 0;
				else if(m_pos.y >= 1000)
					m_pos.y = 1000 - 25;

				//Set our position
				m_rect.x = m_pos.x;
				m_rect.y = m_pos.y;
			}
		}
	}
	else
	{

	}
}

void Unit::draw(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, m_color.x, m_color.y, m_color.w, m_color.h);
	SDL_RenderFillRect(renderer, &m_rect);
}

void Unit::handleInput(InputHandler & input)
{
	m_velocity.zeroVector(); //Reset velocity

	if (input.isButtonHeld("W") || input.isButtonHeld("S")
		|| input.isButtonHeld("A") || input.isButtonHeld("D"))
	{
		if (input.isButtonHeld("W"))
		{
			m_velocity.y = -1;
		}
		else if (input.isButtonHeld("S"))
		{
			m_velocity.y = 1;
		}
		else if (input.isButtonHeld("A"))
		{
			m_velocity.x = -1;
		}
		else if (input.isButtonHeld("D"))
		{
			m_velocity.x = 1;
		}

		//Set move to true
		m_move = true;
	}
	else
	{
		m_move = false;
		m_moveTimer = m_moveSpeed;
	}
}