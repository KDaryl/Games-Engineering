#pragma once
#include "SDL.h"
#include "SDL_thread.h" //Threading
#include "InputHandler.h"
#include <vector>
#include "Grid.h"
#include "Unit.h"
#include <random>

static bool useThreads;
static bool startSearch;
static SDL_mutex * goalAccess;
static std::vector<int> in, last;
static std::vector<bool> ttu; //ttu == thread to update
static int threadCount;

//Hold a vector of enemies to update?
struct ThreadData
{
	ThreadData(int _index, Grid& gPtr, std::vector<Unit*> _units, double& _dt) :
		index(_index),
		gridPtr(&gPtr),
		units(_units),
		dt(&_dt)
	{
	}

	int randInt(int min, int max);
	void aStar(Tile& goal, Tile& from);

	std::vector<Unit*> units;
	Grid * gridPtr;
	int index;
	double* dt;
};

class GameScene
{
public:
	GameScene();
	void handleInput(InputHandler& input);
	void update(double dt);
	void draw(SDL_Renderer* renderer);

	static int agentHandler(void* data);
	int randInt(int min, int max);
private:
	double m_dt; //For threads to update themselves
	std::vector<SDL_Thread*> m_threads; //All our threads
	Grid m_grid;

	Unit m_player;

	std::vector<Unit*> m_units; //Vector of enemy units
};
