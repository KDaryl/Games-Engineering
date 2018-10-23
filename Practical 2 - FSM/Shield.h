#pragma once
#include "State.h"
class Shield : public State
{
private:
	Player* m_player;

public:
	Shield(Player*player) { m_player = player; };
	~Shield() {};

	void idle(Animation* a);
	void shield(Animation* a);
	void jump(Animation* a);
	void crouch(Animation* a);
	void melee(Animation* a);
	void fire(Animation* a);
};

