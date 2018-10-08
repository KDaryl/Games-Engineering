#include "Fire.h"
#include "Idle.h"

void Fire::idle(Animation * a)
{
	std::cout << "Fire to Idle" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}
