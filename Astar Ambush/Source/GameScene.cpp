#include "GameScene.h"

int Unit::pathCost =  -1;

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
			if(m_grid.m_tiles[std::to_string(j) + "," + std::to_string(i)].m_isObstacle == false)
			{ 
				m_units.push_back(new Unit(25 * j, 25 * i, false, m_grid, m_player));
				unitsCreated++;
			}
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
	m_dt = dt;
	m_grid.update(dt);

	//Update player
	m_player.update(dt);

	if (!useThreads)
	{
		//Update all of the units if we arent using threads to do it
		for (auto& unit : m_units)
		{
			if (unit->m_prevPlayerPos != unit->playerPtr()->gridPos())
			{
				unit->setPath(ThreadData::aStar(m_grid.m_tiles[unit->playerPtr()->gridPos()], m_grid.m_tiles[unit->gridPos()], &m_grid, *unit));
				unit->m_prevPlayerPos = unit->playerPtr()->gridPos();
				unit->setCanUpdate(true);
			}

			//Update the unit on this thread
			unit->update(dt);
		}
	}
	else
	{
		//Update all of the units if we arent using threads to do it
		for (auto& unit : m_units)
		{
			unit->update(dt);
		}
	}

	//If the player moves, we need to recalculate our A* ambush spots as not taken
	if (m_player.moving())
		m_grid.setResetSpotsTaken(true);

	for (int i = 0; i < ttu.size(); i++)
		ttu.at(i) = true;
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
					
				}
			}
		}

		//Our critical section so we can access our grid shared data
		SDL_LockMutex(goalAccess);

		//If we are to update the units for this thread, then do it
		if (ttu.at(index))
		{
			//Reset the spots taken variables if we have to
			if (threadData->gridPtr->toReset())
			{
				threadData->gridPtr->resetSpotsBools();
				threadData->gridPtr->setResetSpotsTaken(false);
			}

			for (int i = 0; i < threadData->units.size(); i++)
			{
				Unit* unit = threadData->units.at(i);

				if (unit->m_prevPlayerPos != unit->playerPtr()->gridPos())
				{
					unit->setCanUpdate(false);
					unit->setPath(threadData->aStar(threadData->gridPtr->m_tiles[unit->playerPtr()->gridPos()], threadData->gridPtr->m_tiles[unit->gridPos()], threadData->gridPtr, *unit));
					unit->m_prevPlayerPos = unit->playerPtr()->gridPos();
					unit->setCanUpdate(true);
				}

				//Update the unit on this thread
				//unit->update(*threadData->dt);
			}

			ttu.at(index) = false; //Set our thread to update as false
		}


		in[index] = 0; //Exit

		//Non-critical section, unlock our mutex shared data
		SDL_UnlockMutex(goalAccess);
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

std::vector<Vector2f> ThreadData::aStar(Tile &_goal, Tile & from, Grid* grid, Unit& unit)
{
	Tile* goal = &_goal;
	goal->goalDist = 100000000000;
	goal->spotTaken = true;
	//Create priority queue for distance checking
	std::priority_queue<Tile*, std::vector<Tile*>, TilePosCompare> distQueue;

	distQueue.push(goal);
	bool gotNewGoal = false;

	//Set the goal by deciding the closest point to the goal that is free
	while (distQueue.empty() == false)
	{
		auto current = distQueue.top(); //Get the value on the tope of the queue


		//Look at all neighbours
		for (auto* n : current->neighbours)
		{
			if (n->spotTaken == false)
			{
				gotNewGoal = true;
				goal = n; //Set the new goal
				
				break; //Break from loop, we found a new goal to pathfind to
			}
			else if(n->visited == false && n->m_isObstacle == false)
			{
				n->visited = true;
				n->goalDist = std::abs((n->m_pos.x - goal->m_pos.x) / 25) + std::abs((n->m_pos.y - goal->m_pos.y) / 25);;
				distQueue.push(n);
			}
		}

		if (gotNewGoal)
			break;

		//Remove from the top of the queue
		distQueue.pop();
	}

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
			//Set the goal distance (for ambush)
			t.goalDist = std::numeric_limits<float>().max() - 100000;
			t.fCost = std::numeric_limits<float>().max() - 100000;
			t.gCost = std::numeric_limits<float>().max() - 100000;
			t.hCost = std::numeric_limits<float>().max() - 100000;
			t.closed = false; //Set closed to false
			t.previous = nullptr; //Reset previous ptr
			t.visited = false; //Set visited to false
		}
	}
	unit.setEndPos(unit.getPos());
	from.fCost = 0;
	from.hCost = grid->calculateH(from, *goal);
	from.gCost = 0;
	from.visited = true;

	queue.push(&from);

	//Keep searchign while our queue is not empty
	while (!queue.empty() && !foundPath)
	{
		auto current = queue.top(); //Get the value on the tope of the queue
	
		current->closed = true;
		//If we found the goal
		if (current == goal)
		{
			bool setEnd = false;
			foundPath = true;
			auto prev = current;
			while (nullptr != prev && prev->previous)
			{
				if (prev->spotTaken == false)
				{
					if (setEnd == false)
					{
						////Set the end position of the unit
						unit.setEndPos(prev->m_pos);
						prev->spotTaken = true;
						setEnd = true;
					}
				}

				path.push_back(prev->m_pos);
				prev = prev->previous;
			}

			std::reverse(path.begin(), path.end());

			break; //Break while loop
		}


		//Loop through neighbours
		for (auto& tile : current->neighbours)
		{
			//If the tile is a wall or its closed skip it
			if (tile->m_isObstacle || tile->closed)
				continue;

			auto newG = current->gCost + 1.0f;
			auto newH = grid->calculateH(*tile, *goal);
			auto newF = newG + newH; //+ (unit.unitPathCost / 1.0f);

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

	if (foundPath == false)
		std::cout << "No path found to goal for some reason? \n";

	return path;
}