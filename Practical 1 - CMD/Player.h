#pragma once
#include <iostream>
using namespace std;

class Player
{
public:
	Player();
	~Player();

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

