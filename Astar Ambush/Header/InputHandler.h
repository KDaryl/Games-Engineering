#pragma once
#include "SDL.h"
#include <map>

typedef std::map<std::string, bool> Input;

class InputHandler
{
public:
	InputHandler();

	void updateInput();

private:
};