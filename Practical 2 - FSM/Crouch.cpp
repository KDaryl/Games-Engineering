#include "Crouch.h"
#include "Jump.h"
#include "Idle.h"
#include "Melee.h"
#include "Shield.h"
#include "Fire.h"

void Crouch::idle(Animation * a)
{
	std::cout << "Crouch to Idle" << std::endl;
	m_player->setColor(255, 255, 255); //Just set player to white when idle
	a->setCurrent(new Idle(m_player));
	delete this;
}

void Crouch::crouch(Animation * a)
{
	std::cout << "Already crouching" << std::endl;
}

void Crouch::melee(Animation * a)
{
	std::cout << "Crouch to Melee" << std::endl;
	m_player->melee();
	a->setCurrent(new Melee(m_player));
	delete this;
}

void Crouch::shield(Animation * a)
{
	std::cout << "Crouch to Shield" << std::endl;
	m_player->shield();
	a->setCurrent(new Shield(m_player));
	delete this;
}

void Crouch::fire(Animation * a)
{
	std::cout << "Crouch to Fire" << std::endl;
	m_player->fire();
	a->setCurrent(new Fire(m_player));
	delete this;
}

void Crouch::jump(Animation * a)
{
	std::cout << "Crouch to Jump" << std::endl;
	m_player->jump();
	a->setCurrent(new Jump(m_player));
	delete this;
}
