#pragma once
#include <vector>
#include <iostream>
#include <string>

class Game
{
public:
	Game();
	void run();
	std::vector<int>& values();
private:
	std::vector<int> m_values;
};