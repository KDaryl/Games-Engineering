#pragma once
#include "Component.h"
#include <iostream>

class HealthComponent : public Component
{
public:
	HealthComponent() : health(100) { }
	int getHealth() { return health; }
	void setHealth(int hp) { health = hp; };
private:
	int health;
};