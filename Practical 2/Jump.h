#pragma once
#include "State.h"
class Jump : public State
{
public:
	Jump() {};
	~Jump() {};
	void idle(Animation* a);
};

