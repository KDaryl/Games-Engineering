#include "GameScene.h"

GameScene::GameScene() :
	m_grid(true)
{
	//Initialising gloabal variables
	startSearch = false;
	goalAccess = SDL_CreateMutex(); //Create the goal access mutex (wheter a thread can acces sthe information of a goal or not)
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