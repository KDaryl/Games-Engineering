#pragma once
#include "Character.h";
class Player : public Character
{
public:
	void draw() { cout << "Draw Player" << endl; };
};