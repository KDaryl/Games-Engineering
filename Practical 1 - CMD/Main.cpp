/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "Player.h"
#include "InputHandler.h"
#include "JumpCommand.h"
#include "FireCommand.h"
#include "CrouchCommand.h"
#include "ShieldCommand.h"
#include "MeleeCommand.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	return success;
}

void close()
{
	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Our variables
			//---------

			//Reciever
			Player * player = new Player();

			//Concrete command objects
			JumpCommand *jump = new JumpCommand(player);
			FireCommand *fire = new FireCommand(player);
			CrouchCommand *crouch = new CrouchCommand(player);
			MeleeCommand *melee = new MeleeCommand(player);
			ShieldCommand *shield = new ShieldCommand(player);

			//InputHandler
			InputHandler* inputHandler = new InputHandler();
			//Add our commands to our input handler
			inputHandler->setCommand("Jump", jump);
			inputHandler->setCommand("Fire", fire);
			inputHandler->setCommand("Crouch", crouch);
			inputHandler->setCommand("Shield", shield);
			inputHandler->setCommand("Melee", melee);

			//---------

			cout << "Controls:\nJump: SPACE\nFire: 1\nCrouch: 2\nMelee: 3\nShield: 4\nUndo: U\nRedo: R\n****************\n" << endl;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					//If user presses a key
					else if (e.type == SDL_KEYDOWN)
					{
						auto cmd = inputHandler->handleInput(e); //Get the command from input handler
						if (cmd != nullptr)//If the command is not a nullptr, then execute the command
							cmd->execute();
					}
				}

				//Update the surface
				SDL_UpdateWindowSurface(gWindow);
			}

			delete jump, inputHandler;
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}