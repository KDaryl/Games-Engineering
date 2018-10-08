#pragma once

class Animation
{
	class State* m_current;
public:
	Animation();
	~Animation();
	void setCurrent(State* s) { m_current = s; };
	void update();
	//Animations
	void idle();
	void jump();
	void crouch();
	void fire();
	void melee();
	void shield();
};