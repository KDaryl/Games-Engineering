#include "Jump.h"
#include "Idle.h"

void Jump::idle(Animation * a)
{
	cout << "Jump to Idle" << endl;
	a->setCurrent(new Idle());
	delete this;
}
