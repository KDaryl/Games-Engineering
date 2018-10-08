#include "Player.h"
#include "Idle.h"

Player::Player() { m_animation.setCurrent(new Idle()); } //Set current animation

Player::~Player(){}

void Player::jump()
{
	cout << "Player has jumped" << endl;
	m_animation.jump();
}

void Player::crouch()
{
	cout << "Player has crouched" << endl;
	m_animation.crouch();
}

void Player::shield()
{
	cout << "Player has used shield" << endl;
	m_animation.shield();
}

void Player::fire()
{
	cout << "Player has fired" << endl;
	m_animation.fire();
}

void Player::melee()
{
	cout << "Player has used melee" << endl;
	m_animation.melee();
}

void Player::undoJump()
{
	cout << "Player has undone Jump" << endl;
	m_animation.idle();
}

void Player::undoCrouch()
{
	cout << "Player has undone Crouch" << endl;
	m_animation.idle();
}

void Player::undoShield()
{
	cout << "Player has undone Shield" << endl;
	m_animation.idle();
}

void Player::undoFire()
{
	cout << "Player has undone Fire" << endl;
	m_animation.idle();
}

void Player::undoMelee()
{
	cout << "Player has undone Melee" << endl;
	m_animation.idle();
}
