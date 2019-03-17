#pragma once
#include "SDL.h"
#include "SDL_thread.h" //Threading
#include "InputHandler.h"
#include <vector>
#include "Grid.h"

static bool startSearch;
static SDL_mutex * goalAccess;

class GameScene
{
public:
	GameScene();
	void handleInput(InputHandler& input);
	void update(double dt);
	void draw(SDL_Renderer* renderer);
private:
	std::vector<SDL_Thread*> m_threads; //All our threads
	Grid m_grid;
};

//Example of nProcesses
//void main()
//{
//	for (int i = 0; i < threadCount; i++)
//		in.push_back(0);
//
//	//Copy over in to last
//	last = in;
//
//	for (int i = 0; i < threadCount; i++)
//		threads.push_back(new std::thread(cs, i));
//
//	//Needed to keep the program from finishing
//	while (true) {}
//}
//
//void cs(int index)
//{
//	while (true)
//	{
//		for (int j = 0; j < threadCount - 1; j++)
//		{
//			in[index] = j;
//			last[j] = index;
//
//			for (int k = 0; k < threadCount - 1; k++)
//			{
//				while (last[j] == index && k != index)
//				{
//
//				}
//			}
//		}
//
//		std::cout << "Criticial section of thread: " << index + 1 << std::endl;
//		in[index] = 0; //Exit
//	}
//}
