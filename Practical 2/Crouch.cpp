#include "Crouch.h"
#include "Jump.h"
#include "Idle.h"
#include "Melee.h"
#include "Shield.h"
#include "Fire.h"

void Crouch::idle(Animation * a)
{
	std::cout << "Crouch to Idle" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}

void Crouch::melee(Animation * a)
{
	std::cout << "Crouch to Melee" << std::endl;
	a->setCurrent(new Melee());
	delete this;
}

void Crouch::shield(Animation * a)
{
	std::cout << "Crouch to Shield" << std::endl;
	a->setCurrent(new Shield());
	delete this;
}

void Crouch::fire(Animation * a)
{
	std::cout << "Crouch to Fire" << std::endl;
	a->setCurrent(new Fire());
	delete this;
}
