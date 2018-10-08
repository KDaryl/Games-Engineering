#pragma once
#include "State.h"
class Shield : public State
{
public:
	Shield() {};
	~Shield() {};

	void idle(Animation* a);
};

