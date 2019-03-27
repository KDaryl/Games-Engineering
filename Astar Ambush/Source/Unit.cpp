#include "Unit.h"

Unit::Unit(int x, int y, bool player, Grid& grid, Unit& playerUnit) :
	m_playerPtr(&playerUnit),
	m_gPtr(&grid),
	m_pos(x, y),
	m_isPlayer(player),
	m_moveSpeed(.05f),
	m_moveTimer(m_moveSpeed),
	m_move(true),
	m_velocity(0, 0),
	m_gridPos(std::to_string(x / 25) + "," + std::to_string(y / 25))
{
	Unit::pathCost++; //Increase path cost
	unitPathCost = Unit::pathCost;

	m_rect = { x, y, 25, 25 };

	//Set colour based on our is player boolean
	if (m_isPlayer)
	{
		m_canUpdate = true;
		m_color = { 0, 255, 0, 255 };
	}
	else
	{
		m_canUpdate = false;
		m_prevPlayerPos = ",";
		m_color = { 255, 0, 0, 255 };
	}
}

void Unit::update(double dt)
{
	if (m_canUpdate)
	{
		if (m_isPlayer)
		{
			if (m_move)
			{
				m_moveTimer -= dt;

				if (m_moveTimer <= 0)
				{
					m_moveTimer = m_moveSpeed;

					auto newPos = m_pos + m_velocity * 25;

					if (m_gPtr->m_tiles[std::to_string(int(newPos.x) / 25) + "," + std::to_string(int(newPos.y) / 25)].m_isObstacle == false)
					{

						//Move the player
						m_pos += m_velocity * 25;

						//Clamp players position into the game area
						if (m_pos.x < 0)
							m_pos.x = 0;
						else if (m_pos.x >= 1000)
							m_pos.x = 1000 - 25;
						if (m_pos.y < 0)
							m_pos.y = 0;
						else if (m_pos.y >= 1000)
							m_pos.y = 1000 - 25;

						m_gridPos = std::to_string(int(m_pos.x) / 25) + "," + std::to_string(int(m_pos.y) / 25);

						//Set our position
						m_rect.x = m_pos.x;
						m_rect.y = m_pos.y;
					}
				}
			}
		}
		else
		{
			//If we are to move
			if (m_path.empty() == false)
			{
				//If we have not reached our required estination, move to it
				if (m_currentPathPos != m_path.end())
				{
					if (m_pos != *m_currentPathPos)
					{
						m_moveTimer -= dt;

						if (m_moveTimer <= 0)
						{
							////Set velocity
							if ((*m_currentPathPos).x > m_pos.x)
								m_velocity.x = 1;
							else if ((*m_currentPathPos).x < m_pos.x)
								m_velocity.x = -1;
							else if ((*m_currentPathPos).y > m_pos.y)
								m_velocity.y = 1;
							else if ((*m_currentPathPos).y < m_pos.y)
								m_velocity.y = -1;

							m_moveTimer = m_moveSpeed;

							//Move the unit
							m_pos += m_velocity * 25;

							m_velocity.zeroVector();

							//Clamp players position into the game area
							if (m_pos.x < 0)
								m_pos.x = 0;
							else if (m_pos.x >= 1000)
								m_pos.x = 1000 - 25;
							if (m_pos.y < 0)
								m_pos.y = 0;
							else if (m_pos.y >= 1000)
								m_pos.y = 1000 - 25;

							m_gridPos = std::to_string(int(m_pos.x) / 25) + "," + std::to_string(int(m_pos.y) / 25);

							//Set our position
							m_rect.x = m_pos.x;
							m_rect.y = m_pos.y;
						}
					}

					else if (m_pos == *m_currentPathPos && m_pos != endPos)
					{
						++m_currentPathPos;
						m_velocity.zeroVector();
					}
				}
			}
		}
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
	else if(m_isPlayer)
	{
		m_move = false;
		m_moveTimer = m_moveSpeed;
	}
}