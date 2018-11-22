#include "Test.h"
#include "../Game.h"

void main()
{
	Test test; //Used for assertions
	//Game game;

	game.run();

	//Testing the range
	test.range(game.values());
	test.repeated(game.values());
	test.size(game.values());

	//Testing fake data, should fail here as first line has only 5 values and the second is empty
	test.size({1 ,1, 1, 1, 1,1});
	test.size({ });

	std::cout << "All tests passed" << std::endl;

	system("Pause");
}