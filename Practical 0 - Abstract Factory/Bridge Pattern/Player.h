#pragma once
#include "Character.h"
#include "DrawImpl.h"

class Player : public Character
{
public: 
	Player(DrawAPI* api) { this->api = api; }
	void draw() { api->draw(); }

private:
	DrawAPI * api;
};