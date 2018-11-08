#include "Game.h"

Game::Game()
{
}

void Game::run()
{
	std::vector<int> values = {};
	std::string answer = "";

	bool validString = false;
	
	while (validString == false)
	{
		system("CLS");

		std::cout << "Type your 6 values seperated by a ',' like so:\n1,2,3,4,5,6" << std::endl << std::endl; //Instructions

		std::cin >> answer; //Get the values from the user


		validString = true;

		//Validate answer
		for (auto& c : answer)
		{
			std::string s = std::string(1, c);
			if (s != "," && s != "0" && s != "1" && s != "2" && s != "3" && s != "4" && s != "5" &&
				s != "6" && s != "7" && s != "8" && s != "9")
			{
				validString = false;
				std::cout << "Invalid string, must only contain numbers and ',' between them" << std::endl;
				system("pause");
				break;
			}
		}
	}


	//Get values from the string1
	std::string val = "";
	for (int i = 0; i < answer.size(); i++)
	{
		if (i == (answer.size() - 1))
		{
			val += answer.at(i);
		}
		if (i == (answer.size() - 1) || answer.at(i) == ',')
		{
			values.push_back(std::stoi(val));
			val = "";
		}
		else
		{
			val += answer.at(i);
		}
	}

	m_values = values;
}

std::vector<int>& Game::values()
{
	return m_values;
}
