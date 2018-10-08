#pragma once
#include "State.h"

class Crouch : public State
{
public:
	Crouch() {};
	~Crouch() {};

	void idle(Animation* a);
	void melee(Animation* a);
	void shield(Animation* a);
	void fire(Animation* a);
};

