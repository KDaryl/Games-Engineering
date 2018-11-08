#include "Test.h"
#include "../Game.h"

void main()
{
	Test test; //Used for assertions
	Game game;

	game.run();

	test.range(game.values());
	test.repeated(game.values());
	test.size(game.values());

	std::cout << "All tests passed" << std::endl;

	system("Pause");
}