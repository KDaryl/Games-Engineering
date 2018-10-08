#pragma once
#include "State.h"

class Fire : public State
{
public:
	Fire() {};
	~Fire() {};

	void idle(Animation* a);
};

