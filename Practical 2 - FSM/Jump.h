#pragma once
#include "State.h"
class Jump : public State
{
private:
	Player* m_player;

public:
	Jump(Player*player) { m_player = player; };
	~Jump() {};
	void idle(Animation* a);
	void jump(Animation * a);
	void crouch(Animation* a);
	void melee(Animation* a);
	void fire(Animation* a);
	void shield(Animation* a);
};

