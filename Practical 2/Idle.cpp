#include "Idle.h"
#include "Jump.h"
#include "Shield.h"
#include "Melee.h"
#include "Crouch.h"
#include "Fire.h"

void Idle::jump(Animation * a)
{
	cout << "Idle to Jump" << endl;
	a->setCurrent(new Jump());
	delete this;
}

void Idle::crouch(Animation * a)
{
	cout << "Idle to Crouch" << endl;
	a->setCurrent(new Crouch());
	delete this;
}

void Idle::melee(Animation * a)
{
	cout << "Idle to Melee" << endl;
	a->setCurrent(new Melee());
	delete this;
}

void Idle::fire(Animation * a)
{
	cout << "Idle to Fire" << endl;
	a->setCurrent(new Fire());
	delete this;
}

void Idle::shield(Animation * a)
{
	cout << "Idle to Shield" << endl;
	a->setCurrent(new Shield());
	delete this;
}
