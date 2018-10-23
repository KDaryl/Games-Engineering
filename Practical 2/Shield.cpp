#include "Idle.h"
#include "Jump.h"
#include "Shield.h"
#include "Melee.h"
#include "Crouch.h"
#include "Fire.h"

void Shield::idle(Animation * a)
{
	std::cout << "Shield to Idle" << std::endl;
	a->setCurrent(new Idle(m_player));
	m_player->setColor(255, 255, 255);
	delete this;
}

void Shield::shield(Animation * a)
{
	std::cout << "Already shielding" << std::endl;
}

void Shield::melee(Animation * a)
{
	std::cout << "Shield to Melee" << std::endl;
	m_player->melee();
	a->setCurrent(new Melee(m_player));
	delete this;
}

void Shield::crouch(Animation * a)
{
	std::cout << "Shield to Crouch" << std::endl;
	m_player->crouch();
	a->setCurrent(new Crouch(m_player));
	delete this;
}

void Shield::fire(Animation * a)
{
	std::cout << "Shield to Fire" << std::endl;
	m_player->fire();
	a->setCurrent(new Fire(m_player));
	delete this;
}

void Shield::jump(Animation * a)
{
	std::cout << "Shield to Jump" << std::endl;
	m_player->jump();
	a->setCurrent(new Jump(m_player));
	delete this;
}
