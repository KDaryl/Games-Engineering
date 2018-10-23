#pragma once
#include "Character.h"
class Boss : public Character
{
public:
	void draw() { cout << "Draw Boss" << endl; }
};