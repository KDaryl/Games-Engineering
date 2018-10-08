#include "Melee.h"
#include "Idle.h"

void Melee::idle(Animation * a)
{
	std::cout << "Melee to Idle" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}
