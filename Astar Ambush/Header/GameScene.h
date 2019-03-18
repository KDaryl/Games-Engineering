#pragma once
#include "SDL.h"
#include "SDL_thread.h" //Threading
#include "InputHandler.h"
#include <vector>
#include "Grid.h"
#include "Unit.h"

static bool startSearch;
static SDL_mutex * goalAccess;
static std::vector<int> in, last;
static int threadCount;

//Hold a vector of enemies to update?
struct ThreadData
{
	ThreadData(int _index, Grid& gPtr) :
		index(_index),
		gridPtr(&gPtr)
	{
	}

	void aStar(Tile& goal, Tile& from);

	Grid * gridPtr;
	int index;
};

class GameScene
{
public:
	GameScene();
	void handleInput(InputHandler& input);
	void update(double dt);
	void draw(SDL_Renderer* renderer);

	static int agentHandler(void* data);

private:
	std::vector<SDL_Thread*> m_threads; //All our threads
	Grid m_grid;

	Unit m_player;

	std::vector<Unit> m_units; //Vector of enemy units
};
