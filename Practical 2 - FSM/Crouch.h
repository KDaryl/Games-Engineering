#pragma once
#include "State.h"

class Crouch : public State
{
private:
	Player* m_player;

public:
	Crouch(Player*player) { m_player = player; };
	~Crouch() {};

	void idle(Animation* a);
	void crouch(Animation* a);
	void jump(Animation* a);
	void melee(Animation* a);
	void fire(Animation* a);
	void shield(Animation* a);
};

