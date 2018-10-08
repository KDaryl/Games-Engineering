#pragma once
#include "Animation.h"
#include <iostream>
using namespace std;

class State
{
public:
	virtual void idle(Animation* a) { cout << "State:Idling" << endl; }
	virtual void jump(Animation* a) { cout << "State:Jump" << endl; }
	virtual void fire(Animation* a) { cout << "State:Fire" << endl; }
	virtual void melee(Animation* a) { cout << "State:Melee" << endl; }
	virtual void crouch(Animation* a) { cout << "State:Crouch" << endl; }
	virtual void shield(Animation* a) { cout << "State:Shield" << endl; }
};