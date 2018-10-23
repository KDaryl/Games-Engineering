#pragma once
#include "State.h"

class Melee : public State
{
private:
	Player* m_player;

public:
	Melee(Player*player) { m_player = player; };
	~Melee() {};

	void idle(Animation* a);
	void melee(Animation* a);
	void jump(Animation* a);
	void crouch(Animation* a);
	void fire(Animation* a);
	void shield(Animation* a);
};