#include "GameScene.h"

GameScene::GameScene() :
	m_grid(true)
{

	//Initialising gloabal variables
	threadCount = 4;
	startSearch = false;
	goalAccess = SDL_CreateMutex(); //Create the goal access mutex (wheter a thread can access the information of a goal or not)

	for (int i = 0; i < threadCount; i++)
		in.push_back(i);

	//Copy in, into last
	last = in;

	//Currently executes each thread at least once
	for (int i = 0; i < threadCount; i++)
		m_threads.push_back(SDL_CreateThread(agentHandler, "Test", (void *)new ThreadData(i)));
}

void GameScene::handleInput(InputHandler & input)
{
	if (input.isButtonPressed("Tab"))
		m_grid.setDraw(!m_grid.getDraw());
}

void GameScene::update(double dt)
{
	m_grid.update(dt);
}

void GameScene::draw(SDL_Renderer * renderer)
{
	//Draw grid
	m_grid.draw(renderer);
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
					//std::cout << "Thread: " << index + 1 << " is working\n";
					SDL_UnlockMutex(goalAccess);
				}
			}
		}

		std::cout << "Criticial section of thread: " << index + 1 << std::endl;
		in[index] = 0; //Exit
	}
	return 0;
}
