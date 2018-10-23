#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::jump()
{
	cout << "Player has jumped" << endl;
}

void Player::crouch()
{
	cout << "Player has crouched" << endl;
}

void Player::shield()
{
	cout << "Player has used shield" << endl;
}

void Player::fire()
{
	cout << "Player has fired" << endl;
}

void Player::melee()
{
	cout << "Player has used melee" << endl;
}

void Player::undoJump()
{
	cout << "Player has undone Jump" << endl;
}

void Player::undoCrouch()
{
	cout << "Player has undone Crouch" << endl;
}

void Player::undoShield()
{
	cout << "Player has undone Shield" << endl;
}

void Player::undoFire()
{
	cout << "Player has undone Fire" << endl;
}

void Player::undoMelee()
{
	cout << "Player has undone Melee" << endl;
}
