#include "Game.h"

Game::Game(int fps) :
	m_msPerFrame(1.0 / fps), //Get the target fps
	m_clearRect({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }),
	m_window(NULL),
	m_screenSurface(NULL),
	m_quit(false)
{
}

void Game::update(double dt)
{
	m_input.updateInput(); //Update the input
	m_gameScene.handleInput(m_input); //Handle Input

	m_gameScene.update(dt);//Update the game scene
}

void Game::draw()
{
	//Clear the screen
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	//Draw the current scene
	m_gameScene.draw(m_renderer);

	//Render everything drawn to the renderer
	SDL_RenderPresent(m_renderer);
}

void Game::processEvents(SDL_Event& e)
{
	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			//Set our bool to true
			m_quit = true;
		}

		//If keydown event
		if (e.type == SDL_KEYDOWN)
		{
			//If key is escape
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				//Exit game
				m_quit = true;
			}
		}
	}
}


void Game::run()
{

	//Create our SDL event variable
	SDL_Event e;
	double dt = 0;
	double frameTime = 0;
	double counterTime = 0;
	int frames = 0;
	auto now = std::chrono::system_clock::now();
	auto before = std::chrono::system_clock::now();

	//While our bool is false, loop indefinitely
	while (!m_quit)
	{
		now = std::chrono::system_clock::now();
		dt = std::chrono::duration<double>(now - before).count(); //Add to dt
		frameTime += dt; //Add DT to our frametime
		counterTime += dt; //Add to our counter time

		//Update the game
		update(dt);

		//If its time for an draw do it
		if (frameTime >= m_msPerFrame)
		{
			//Process any events that have occured
			processEvents(e);

			//Draw the Game
			draw();

			//Take away ms per frame from our frametime
			frameTime -= m_msPerFrame;
		}

		frames++;

		//If 1 second has passed
		if (counterTime >= 1.0f)
		{
			counterTime -= 1; //Remove 1 second from the counter
			std::cout << "FPS: " << frames << "\n";
			frames = 0; //Reset frames per second
		}


		//Make before time equal to the current time
		before = now;
	}

	//Call close if our game loop is over
	close();
}

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		m_window = SDL_CreateWindow("A* Ambush - Daryl Keogh", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{

			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
			//Get window surface
			m_screenSurface = SDL_GetWindowSurface(m_window);
		}

	}
	return success;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;

	return success;
}

void Game::close()
{
	//Destroy window
	SDL_DestroyWindow(m_window);

	m_window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}