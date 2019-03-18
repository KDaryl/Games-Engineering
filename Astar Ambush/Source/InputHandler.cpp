#include "InputHandler.h"

InputHandler::InputHandler() :
	mouseX(0),
	mouseY(0)
{
	//Keep a pointer to the keyboard state
	m_keyStates = SDL_GetKeyboardState(NULL);

	//Add buttons to our input handler
	m_current["W"] = false;
	m_current["A"] = false;
	m_current["S"] = false;
	m_current["D"] = false;
	m_current["LEFT_CLICK"] = false;
	m_current["RIGHT_CLICK"] = false;
	m_current["Tab"] = false;
	m_current["Space"] = false;

	//Copy over our keys to our previous map
	m_previous = m_current;
}

void InputHandler::updateInput()
{
	m_previous = m_current; //Set the previous

	//Get mouse Position and the current mouse button clicked
	auto m = SDL_GetRelativeMouseState(&mouseX, &mouseY);
	
	//Check keys
	m_current["W"] = m_keyStates[SDL_SCANCODE_W];
	m_current["A"] = m_keyStates[SDL_SCANCODE_A];
	m_current["S"] = m_keyStates[SDL_SCANCODE_S];
	m_current["D"] = m_keyStates[SDL_SCANCODE_D];
	m_current["Tab"] = m_keyStates[SDL_SCANCODE_TAB];
	m_current["LEFT_CLICK"] = m == 1 ? true : false;
	m_current["RIGHT_CLICK"] = m == 4 ? true : false;
	m_current["Space"] = m_keyStates[SDL_SCANCODE_SPACE];
}

bool InputHandler::isButtonPressed(std::string btn)
{
	return m_current[btn] && !m_previous[btn];
}

bool InputHandler::isButtonHeld(std::string btn)
{
	return m_current[btn];
}
