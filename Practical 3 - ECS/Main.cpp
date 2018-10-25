/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "Entity.h"
#include "RenderComponent.h"
#include "RenderSystem.h"
#include "AiSystem.h"
#include "ControlSystem.h"
#include "PositionComponent.h"
#include "CollisionSystem.h"
#include "HealthComponent.h"

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
		gWindow = SDL_CreateWindow("Entity Component System", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
			Entity player("Player"), alien("Alien"), dog("Dog"), cat("Cat");
			RenderSystem renderSystem;
			ControlSystem controlSystem;
			CollisionSystem collisionSystem;
			AiSystem aiSystem;
			RenderComponent pRenderComp, aRenderComp, dRenderComp, cRenderComp;
			PositionComponent pPosComp, aPosComp, dPosComp, cPosComp;
			HealthComponent pHpComp, aHpComp, dHpComp, cHpComp; //Alien, dog, cat health, Player has unlimited health

			//Set component values
			/* Player - Orange */
			pPosComp.setPosition(100, 100);
			pRenderComp.setColor(255, 125, 70);
			pRenderComp.setRect(pPosComp.getPosition().first - 25, pPosComp.getPosition().second -25, 50, 50);
			/* Alien - Green */
			aPosComp.setPosition(400, 350);
			aRenderComp.setColor(125, 255, 70);
			aRenderComp.setRect(aPosComp.getPosition().first - 25, aPosComp.getPosition().second - 25, 50, 50);
			/* Dog - Yellow */
			dPosComp.setPosition(500, 420);
			dRenderComp.setColor(255, 255, 70);
			dRenderComp.setRect(dPosComp.getPosition().first - 25, dPosComp.getPosition().second - 25, 50, 50);
			/* Cat - Blue */
			cPosComp.setPosition(200, 200);
			cRenderComp.setColor(70, 255, 255);
			cRenderComp.setRect(cPosComp.getPosition().first - 25, cPosComp.getPosition().second - 25, 50, 50);

			//Add components to Entities
			/* Player - Orange */
			player.addComponent("RenderComp", pRenderComp);
			player.addComponent("PositionComp", pPosComp);
			player.addComponent("HealthComp", pHpComp);
			/* Alien - Green */
			alien.addComponent("RenderComp", aRenderComp);
			alien.addComponent("PositionComp", aPosComp);
			alien.addComponent("HealthComp", aHpComp);
			/* Dog - Yellow */
			dog.addComponent("RenderComp", dRenderComp);
			dog.addComponent("PositionComp", dPosComp);
			dog.addComponent("HealthComp", dHpComp);
			/* Cat - Blue */
			cat.addComponent("RenderComp", cRenderComp);
			cat.addComponent("PositionComp", cPosComp);
			cat.addComponent("HealthComp", cHpComp);

			//Add entities/objects to our systems
			renderSystem.addEntity(player);
			renderSystem.addEntity(alien);
			renderSystem.addEntity(dog);
			renderSystem.addEntity(cat);

			controlSystem.addEntity(player);

			aiSystem.addEntity(alien);

			collisionSystem.addEntity(player);
			collisionSystem.addEntity(alien);
			collisionSystem.addEntity(dog);
			collisionSystem.addEntity(cat);

			renderSystem.setWindow(*gScreenSurface);
			//---------

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
					//If user presses a key, call the control system to handle input
					else if (e.type == SDL_KEYDOWN)
					{
						controlSystem.handleInput(e); //Handle input in the control system
					}
				}

				//UPDATE
				aiSystem.update(SCREEN_WIDTH);
				collisionSystem.handleCollisions();

				//DRAW
				//Clear the entire screen
				SDL_FillRect(gScreenSurface, NULL, 0x000000);

				renderSystem.draw(); //Draw all of our render components

				//Update the surface
				SDL_UpdateWindowSurface(gWindow);

				system("CLS");
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}