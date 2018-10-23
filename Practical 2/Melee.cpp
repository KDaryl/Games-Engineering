#include "Idle.h"
#include "Jump.h"
#include "Shield.h"
#include "Melee.h"
#include "Crouch.h"
#include "Fire.h"

void Melee::idle(Animation * a)
{
	std::cout << "Melee to Idle" << std::endl;
	a->setCurrent(new Idle(m_player));
	m_player->setColor(255, 255, 255);
	delete this;
}

void Melee::melee(Animation * a)
{
	std::cout << "Melee again" << std::endl;
	m_player->melee();
}

void Melee::crouch(Animation * a)
{
	std::cout << "Melee to Crouch" << std::endl;
	m_player->crouch();
	a->setCurrent(new Crouch(m_player));
	delete this;
}

void Melee::shield(Animation * a)
{
	std::cout << "Melee to Shield" << std::endl;
	m_player->shield();
	a->setCurrent(new Shield(m_player));
	delete this;
}

void Melee::fire(Animation * a)
{
	std::cout << "Melee to Fire" << std::endl;
	m_player->fire();
	a->setCurrent(new Fire(m_player));
	delete this;
}

void Melee::jump(Animation * a)
{
	std::cout << "Melee to Jump" << std::endl;
	m_player->jump();
	a->setCurrent(new Jump(m_player));
	delete this;
}
