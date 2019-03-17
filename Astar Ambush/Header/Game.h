#ifndef GAME_H
#define GAME_H

//My classes
#include "InputHandler.h"
#include "GameScene.h"

//Others
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <bitset>
#include <thread>

class Game
{
public:
	Game(int fps);

	//Update the game passing in delta time
	void update(double dt);

	//Draw game components
	void draw();

	void processEvents(SDL_Event& e);

	void run();
	//Starts up SDL and creates window
	bool init();
	//Loads media
	bool loadMedia();
	//Frees media and shuts down SDL
	void close();

private:
	//Screen dimension constants
	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HEIGHT = 1000;

	//The window we'll be rendering to
	SDL_Window* m_window;
	//The surface contained by the window
	SDL_Surface* m_screenSurface;
	//The renderer, we will use this to draw images
	SDL_Renderer* m_renderer;

	InputHandler m_input;
	GameScene m_gameScene;

	float m_msPerFrame;
	bool m_quit;
	SDL_Rect m_clearRect;
};

#endif