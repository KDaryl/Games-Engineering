#include "Player.h"

void main()
{
	DrawAPI* api = new DrawImpl();
	Character* character = new Player(api);
	character->draw();

	system("pause");
}