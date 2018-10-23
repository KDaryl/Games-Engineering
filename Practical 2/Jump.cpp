#include "Idle.h"
#include "Jump.h"
#include "Shield.h"
#include "Melee.h"
#include "Crouch.h"
#include "Fire.h"

void Jump::idle(Animation * a)
{
	cout << "Jump to Idle" << endl;
	a->setCurrent(new Idle(m_player));
	m_player->setColor(255, 255, 255);
	delete this;
}

void Jump::jump(Animation * a)
{
	std::cout << "Already Jumping" << std::endl;
}

void Jump::melee(Animation * a)
{
	std::cout << "Jump to Melee" << std::endl;
	m_player->melee();
	a->setCurrent(new Melee(m_player));
	delete this;
}

void Jump::shield(Animation * a)
{
	std::cout << "Jump to Shield" << std::endl;
	m_player->shield();
	a->setCurrent(new Shield(m_player));
	delete this;
}

void Jump::fire(Animation * a)
{
	std::cout << "Jump to Fire" << std::endl;
	m_player->fire();
	a->setCurrent(new Fire(m_player));
	delete this;
}

void Jump::crouch(Animation * a)
{
	std::cout << "Jump to Crouch" << std::endl;
	m_player->crouch();
	a->setCurrent(new Crouch(m_player));
	delete this;
}
