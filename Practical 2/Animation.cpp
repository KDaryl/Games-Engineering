#include "Animation.h"
#include "Player.h"
#include "Idle.h"
#include "Jump.h"
#include "Shield.h"
#include "Melee.h"
#include "Crouch.h"
#include "Fire.h"

Animation::Animation(Player* player)
{
	m_player = player;
	m_current = new Idle(player);
}

Animation::~Animation()
{
}


void Animation::idle()
{
	m_current->idle(this);
}

void Animation::jump()
{
	m_current->jump(this);
}

void Animation::crouch()
{
	m_current->crouch(this);
}

void Animation::fire()
{
	m_current->fire(this);
}

void Animation::melee()
{
	m_current->melee(this);
}

void Animation::shield()
{
	m_current->shield(this);
}
