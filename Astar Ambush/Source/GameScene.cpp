#include "GameScene.h"

GameScene::GameScene() :
	m_dt(0),
	m_grid(true),
	m_player(500, 500, true, m_grid)
{
	//Set wheter to use threads or not
	useThreads = true;
	threadCount = 4;
	 
	int noOfUnits = 400;

	//Create our units
	int unitsCreated = 0;
	for (int i = 0; i < 40 && unitsCreated < noOfUnits; i++)
	{
		for (int j = 0; j < 40 && unitsCreated < noOfUnits; j++)
		{
			m_units.push_back(new Unit(25 * j, 25 * i, false, m_grid));
			unitsCreated++;
		}
	}

	if (useThreads)
	{
		std::vector<std::vector<Unit*>> unitsSplit; //Split units

		//Initialising gloabal variables
		startSearch = false;
		goalAccess = SDL_CreateMutex(); //Create the goal access mutex (wheter a thread can access the information of a goal or not)

		//Loop for as many threads as we have and split our units evenly
		for (int i = 0; i < threadCount; i++)
		{
			auto start = m_units.begin() + (m_units.size() / threadCount) * i;
			std::vector<Unit*> temp(start, start + (m_units.size() / threadCount));
			unitsSplit.push_back(temp);

			ttu.push_back(false);
		}

		for (int i = 0; i < threadCount; i++)
			in.push_back(i);

		//Copy in, into last
		last = in;

		//Currently executes each thread at least once
		for (int i = 0; i < threadCount; i++)
			m_threads.push_back(SDL_CreateThread(agentHandler, "Test", (void *)new ThreadData(i, m_grid, unitsSplit.at(i), m_dt)));
	}
}

void GameScene::handleInput(InputHandler & input)
{
	if (input.isButtonPressed("Tab"))
		m_grid.setDraw(!m_grid.getDraw());

	//Handkle input for the player
	m_player.handleInput(input);
}

void GameScene::update(double dt)
{
	for (int i = 0; i < ttu.size(); i++)
		ttu.at(i) = true;

	m_dt = dt;
	m_grid.update(dt);

	//Update player
	m_player.update(dt);

	if (!useThreads)
	{
		//Update all of the units if we arent using threads to do it
		for (auto& unit : m_units)
		{
			unit->setVelocity(0, 0);

			auto direct = randInt(0, 1);
			auto val = randInt(0, 1);

			if (direct == 0)
			{
				unit->setVelocity(0, val == 0 ? -1 : 1);
			}
			else
			{
				unit->setVelocity(val == 0 ? -1 : 1, 0);
			}

			//Update the unit on this thread
			unit->update(dt);
		}
	}
}

void GameScene::draw(SDL_Renderer * renderer)
{
	//Draw grid
	m_grid.draw(renderer);

	//Draw all other units
	for (auto& unit : m_units)
		unit->draw(renderer);

	//Draw the player
	m_player.draw(renderer);

}

int GameScene::agentHandler(void* data)
{
	//The index of the thread
	auto threadData = static_cast<ThreadData*>(data);
	int index = threadData->index;
	while (true)
	{
		for (int j = 0; j < threadCount - 1; j++)
		{
			in[index] = j;
			last[j] = index;

			for (int k = 0; k < threadCount - 1; k++)
			{
				while (last[j] == index && k != index)
				{
					SDL_LockMutex(goalAccess);

					//If we are to update the units for this thread, then do it
					if (ttu.at(index))
					{
						for (auto& unit : threadData->units)
						{
							unit->setVelocity(0, 0);

							auto direct = threadData->randInt(0, 1);
							auto val = threadData->randInt(0, 1);

							if (direct == 0)
							{
								unit->setVelocity(0, val == 0 ? -1 : 1);
							}
							else
							{
								unit->setVelocity(val == 0 ? -1 : 1, 0);
							}

							//Update the unit on this thread
							unit->update(*threadData->dt);
						}

						ttu.at(index) = false;
					}			

					SDL_UnlockMutex(goalAccess);
				}
			}
		}

		//std::cout << "Criticial section of thread: " << index + 1 << std::endl;
		in[index] = 0; //Exit
	}
	return 0;
}

int GameScene::randInt(int min, int max)
{
	std::random_device rseed;
	std::mt19937 rng(rseed());
	std::uniform_int<int> dist(min, max);
	return dist(rng);
}

int ThreadData::randInt(int min, int max)
{
	std::random_device rseed;
	std::mt19937 rng(rseed());
	std::uniform_int<int> dist(min, max);
	return dist(rng);
}

void ThreadData::aStar(Tile & goal, Tile & from)
{
}