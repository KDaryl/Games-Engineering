#pragma once
#include "State.h"

class Fire : public State
{
private:
	Player* m_player;

public:
	Fire(Player*player) { m_player = player; };
	~Fire() {};

	void idle(Animation* a);
	void fire(Animation* a);
	void jump(Animation* a);
	void crouch(Animation* a);
	void melee(Animation* a);
	void shield(Animation* a);
};

