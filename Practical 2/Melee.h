#pragma once
#include "State.h"

class Melee : public State
{
public:
	Melee() {};
	~Melee() {};

	void idle(Animation* a);
};