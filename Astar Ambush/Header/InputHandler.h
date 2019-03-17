#pragma once
#include "SDL.h"
#include "Vector2f.h"
#include <map>

typedef std::map<std::string, bool> Input;

class InputHandler
{
public:
	InputHandler();

	void updateInput();

	bool isButtonPressed(std::string btn);
	bool isButtonHeld(std::string btn);
	Vector2f mousePosition() { return Vector2f(mouseX, mouseY); }
private:
	Input m_current, m_previous;
	const Uint8* m_keyStates;
	int mouseX, mouseY;
};