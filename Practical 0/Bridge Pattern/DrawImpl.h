#pragma once
#include "DrawAPI.h"

class DrawImpl : public DrawAPI
{
public:
	void draw() { cout << "Draw Impl" << endl; }
};