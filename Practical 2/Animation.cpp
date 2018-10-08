#include "Animation.h"
#include "Idle.h"

Animation::Animation()
{
	m_current = new Idle();
}

Animation::~Animation()
{
}

void Animation::update()
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
