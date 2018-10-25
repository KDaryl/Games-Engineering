#pragma once
#include "Command.h"
#include <SDL.h>
#include <map>
#include <vector>

class InputHandler
{
public:
	InputHandler() : canRedo(false), canUndo(true){}
	Command* handleInput(SDL_Event& e) 
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE: //Jump
			previous = commands["Jump"];
			return previous;
			break;
		case SDLK_1: //Fire
			previous = commands["Fire"];
			return previous;
			break;
		case SDLK_2: //Crouch
			previous = commands["Crouch"];
			return previous;
			break;
		case SDLK_3: //Melee
			previous = commands["Melee"];
			return previous;
			break;
		case SDLK_4: //Shield
			previous = commands["Shield"];
			return previous;
			break;
		case SDLK_u: //Undo
			//if (previous && canUndo)
			//{
			//	previous->undo();

			//	canRedo = true; //Set it so that we can redo
			//	canUndo = false;
			//}
			if (previous)
			{
				previous->undo();
			}
			return nullptr;
			break;
		case SDLK_r: //Redo
			//if (previous && canRedo)
			//{
			//	previous->execute();

			//	canRedo = false; //Set it so that we cant redo
			//	canUndo = true;
			//}

			if (previous)
			{
				previous->execute();
			}
			return nullptr;
			break;
		default: //Return nullptr
			return nullptr;
			break;
		}
	};

	void setCommand(string name, Command* cmd)
	{
		commands[name] = cmd;
	}
private:
	//Our Map of commands
	map<string, Command*> commands;
	Command* previous;
	bool canRedo, canUndo;
};