#include "Shield.h"
#include "Idle.h"

void Shield::idle(Animation * a)
{
	std::cout << "Shield to Idle" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}
