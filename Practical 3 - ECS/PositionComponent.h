#pragma once
#include "Component.h"
#include <iostream>

typedef std::pair<float, float> Vector2D;

class PositionComponent : public Component
{
public:
	PositionComponent() { position.first = 0, position.second = 0; }
	Vector2D getPosition() { return position; }
	void setPosition(float x, float y) { position.first = x, position.second = y; };
	void setPosition(Vector2D pos) { position = pos; }
private:
	Vector2D position;
};