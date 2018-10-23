#include "Player.h"
#include "Idle.h"

Player::Player() :
	m_animation(this) //Pass the player to its animation object, this means we can call the specified methods for actions
{ 
	m_animation.setCurrent(new Idle(this)); //Set current animation
	m_rect.x = 640 / 2.0 - (125 / 2.0);
	m_rect.y = 480 / 2.0 - (125 / 2.0);
	m_rect.h = 125;
	m_rect.w = 125;

	setColor(255, 255, 255);
} 

Player::~Player(){}


void Player::draw(SDL_Surface & surface)
{
	SDL_FillRect(&surface, &m_rect, SDL_MapRGB(surface.format, m_color.r, m_color.g, m_color.b));
}

void Player::setColor(int r, int g, int b)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
}

void Player::jump()
{
	cout << "Player has jumped" << endl;
	setColor(51, 54, 232); //Blue
}

void Player::crouch()
{
	cout << "Player has crouched" << endl;
	setColor(216, 41, 26); //Red
}

void Player::shield()
{
	cout << "Player has used shield" << endl;
	setColor(232, 232, 16); //Yellow
}

void Player::fire()
{
	cout << "Player has fired" << endl;
	setColor(16, 232, 23); //Green
}

void Player::melee()
{
	cout << "Player has used melee" << endl;
	setColor(181, 18, 226); //Purple
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
