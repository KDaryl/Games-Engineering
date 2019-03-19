#include "GameScene.h"

GameScene::GameScene() :
	m_dt(0),
	m_grid(true),
	m_player(500, 500, true, m_grid, m_player)
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
			m_units.push_back(new Unit(25 * j, 25 * i, false, m_grid, m_player));
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
			m_threads.push_back(SDL_CreateThread(agentHandler, "Test", (void *)new ThreadData(i, &m_grid, unitsSplit.at(i), m_dt)));
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
						for(int i = 0; i < threadData->units.size(); i++)
						{
							Unit* unit = threadData->units.at(i);

							if (unit->m_prevPlayerPos != unit->playerPtr()->gridPos())
							{
								unit->setPath(threadData->aStar(threadData->gridPtr->m_tiles[unit->playerPtr()->gridPos()], threadData->gridPtr->m_tiles[unit->gridPos()], threadData->gridPtr));
								unit->m_prevPlayerPos = unit->playerPtr()->gridPos();
							}
							
							//Update the unit on this thread
							unit->update(*threadData->dt);
						}

						ttu.at(index) = false; //Set our thread to update as false
					}			

					SDL_UnlockMutex(goalAccess);
				}
			}
		}

		std::cout << "Criticial section of thread: " << index + 1 << std::endl;
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

std::vector<Vector2f> ThreadData::aStar(Tile & goal, Tile & from, Grid* grid)
{
	bool foundPath = false;
	std::vector<Vector2f> path;
	//Create priority queue
	std::priority_queue<Tile*, std::vector<Tile*>, TileCompare> queue;

	for (auto& tile : grid->m_tiles)
	{
		auto& t = tile.second;
		//Only do if its not an obstacle
		if (t.m_isObstacle == false)
		{
			t.fCost = std::numeric_limits<float>().max() - 100000;
			t.gCost = std::numeric_limits<float>().max() - 100000;;
			t.hCost = std::numeric_limits<float>().max() - 100000;;
			t.previous = nullptr; //Reset previous ptr
			t.visited = false; //Set visited to false
		}
	}
	from.fCost = 0;
	from.hCost = grid->calculateH(from, goal);
	from.gCost = 0;
	from.visited = true;

	queue.push(&from);

	//Keep searchign while our queue is not empty
	while (!queue.empty() && !foundPath)
	{
		auto current = queue.top(); //Get the value on the tope of the queue
	
		//If we found the goal
		if (current == &goal)
		{
			foundPath = true;
			auto prev = current;
			while (nullptr != prev && prev->previous)
			{
				path.push_back(prev->m_pos);
				prev = prev->previous;
			}

			std::reverse(path.begin(), path.end());

			break; //Break while loop
		}

		auto nbs = neighbours(*current, grid);

		//Loop through neighbours
		for (auto& tile : nbs)
		{
			auto newG = current->gCost + 1.0f;
			auto newH = grid->calculateH(*tile, goal);
			auto newF = newG + newH;

			//If we found a better path
			if (tile->visited == false || tile->gCost > newG)
			{
				tile->fCost = newF;
				tile->gCost = newG;
				tile->hCost = newH;
				tile->previous = current;
				tile->visited = true;
				queue.push(tile);
			}
		}

		//Remove from the top of the queue
		queue.pop();
	}

	return path;
}

std::vector<Tile*> ThreadData::neighbours(Tile & from, Grid* grid)
{
	std::vector<Tile*> neighbours;
	int x = from.m_gridPosVec.x;
	int y = from.m_gridPosVec.y;

	if (x - 1 >= 0)
	{
		auto tile = grid->m_tiles[std::to_string(x - 1) + "," + std::to_string(y)];
		if (tile.m_isObstacle == false)
			neighbours.push_back(&grid->m_tiles[std::to_string(x - 1) + "," + std::to_string(y)]);
	}
	if (x + 1 < 40)
	{
		auto tile = grid->m_tiles[std::to_string(x + 1) + "," + std::to_string(y)];
		if (tile.m_isObstacle == false)
			neighbours.push_back(&grid->m_tiles[std::to_string(x + 1) + "," + std::to_string(y)]);
	}
	if (y - 1 >= 0)
	{
		auto tile = grid->m_tiles[std::to_string(x) + "," + std::to_string(y - 1)];
		if (tile.m_isObstacle == false)
			neighbours.push_back(&grid->m_tiles[std::to_string(x) + "," + std::to_string(y - 1)]);
	}
	if (y + 1 < 40)
	{
		auto tile = grid->m_tiles[std::to_string(x) + "," + std::to_string(y + 1)];
		if (tile.m_isObstacle == false)
			neighbours.push_back(&grid->m_tiles[std::to_string(x) + "," + std::to_string(y + 1)]);
	}

	return neighbours;
}
