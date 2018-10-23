#include "Idle.h"
#include "Jump.h"
#include "Shield.h"
#include "Melee.h"
#include "Crouch.h"
#include "Fire.h"

void Fire::idle(Animation * a)
{
	std::cout << "Fire to Idle" << std::endl;
	m_player->setColor(255, 255, 255);
	a->setCurrent(new Idle(m_player));
	delete this;
}

void Fire::fire(Animation * a)
{
	std::cout << "Firing again" << std::endl;
	m_player->fire();
}

void Fire::melee(Animation * a)
{
	std::cout << "Fire to Melee" << std::endl;
	m_player->melee();
	a->setCurrent(new Melee(m_player));
	delete this;
}

void Fire::shield(Animation * a)
{
	std::cout << "Fire to Shield" << std::endl;
	m_player->shield();
	a->setCurrent(new Shield(m_player));
	delete this;
}

void Fire::crouch(Animation * a)
{
	std::cout << "Fire to Crouch" << std::endl;
	m_player->crouch();
	a->setCurrent(new Crouch(m_player));
	delete this;
}

void Fire::jump(Animation * a)
{
	std::cout << "Fire to Jump" << std::endl;
	m_player->jump();
	a->setCurrent(new Jump(m_player));
	delete this;
}
