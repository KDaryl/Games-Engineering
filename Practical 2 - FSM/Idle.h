#pragma once
#include "State.h"
#include "Animation.h"

class Idle : public State
{
private:
	Player* m_player;

public:
	Idle(Player*player) { m_player = player; };
	~Idle() {};
	void jump(Animation* a);
	void crouch(Animation* a);
	void melee(Animation* a);
	void fire(Animation* a);
	void shield(Animation* a);
};