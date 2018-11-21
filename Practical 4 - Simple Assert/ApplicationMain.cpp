#include "Game.h"

//Declaring boolean checkers
bool hasSixValues(std::vector<int>& v);
bool inRange(std::vector<int>& v);
bool notRepeated(std::vector<int>& v);

void main()
{
	Game game; //Create the game and run it

	bool goodInput = false;

	while (goodInput == false)
	{
		game.run(); //Run the game
		goodInput = hasSixValues(game.values());
		if (!goodInput)
			std::cout << "did not provide 6 values" << std::endl;
		else
		{
			goodInput = inRange(game.values());
			if (!goodInput)
				std::cout << "value(s) were not in the range of 1 - 46" << std::endl;
			else
			{
				goodInput = notRepeated(game.values());
				if (!goodInput)
					std::cout << "value(s) were repeated" << std::endl;
			}
		}
		if (!goodInput)
			system("pause");
	}
}

bool hasSixValues(std::vector<int>& v)
{
	bool rightSize = true;

	if (v.size() == 6)
		rightSize = true;
	else
		rightSize = false;

	return rightSize;
}

bool inRange(std::vector<int>& v)
{
	for (auto& val : v)
	{
		if (val < 1 || val > 46)
			return false;
	}

	return true;
}

bool notRepeated(std::vector<int>& v)
{
	for (auto& val : v)
	{
		if (std::count(v.begin(), v.end(), val) > 1)
			return false;
	}

	return true;
}