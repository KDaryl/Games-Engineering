#pragma once

class Animation
{
	class State* m_current;
	class Player* m_player;

public:
	Animation(Player* player);
	~Animation();
	void setCurrent(State* s) { m_current = s; };

	//Animations
	void idle();
	void jump();
	void crouch();
	void fire();
	void melee();
	void shield();
};