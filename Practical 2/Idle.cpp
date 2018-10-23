#include "Idle.h"
#include "Jump.h"
#include "Shield.h"
#include "Melee.h"
#include "Crouch.h"
#include "Fire.h"

void Idle::jump(Animation * a)
{
	cout << "Idle to Jump" << endl;
	m_player->jump();
	a->setCurrent(new Jump(m_player));
	delete this;
}

void Idle::crouch(Animation * a)
{
	cout << "Idle to Crouch" << endl;
	m_player->crouch();
	a->setCurrent(new Crouch(m_player));
	delete this;
}

void Idle::melee(Animation * a)
{
	cout << "Idle to Melee" << endl;
	m_player->melee();
	a->setCurrent(new Melee(m_player));
	delete this;
}

void Idle::fire(Animation * a)
{
	cout << "Idle to Fire" << endl;
	m_player->fire();
	a->setCurrent(new Fire(m_player));
	delete this;
}

void Idle::shield(Animation * a)
{
	cout << "Idle to Shield" << endl;
	m_player->shield();
	a->setCurrent(new Shield(m_player));
	delete this;
}
