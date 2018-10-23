#pragma once
#include "Animation.h"
#include "SDL.h"
#include <iostream>
using namespace std;

class Player
{
private:
	Animation m_animation;

	SDL_Color m_color;
	SDL_Rect m_rect;
public:
	Player();
	~Player();
	void draw(SDL_Surface& surface);

	void setColor(int r, int g, int b);
	Animation& getAnimation() { return m_animation; }

	//Our 5 player actions
	void jump();
	void crouch();
	void shield(); 
	void fire();
	void melee();

	//Our undo actions
	void undoJump();
	void undoCrouch();
	void undoShield();
	void undoFire();
	void undoMelee();
};

