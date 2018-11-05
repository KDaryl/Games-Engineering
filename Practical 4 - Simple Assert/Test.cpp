#include <assert.h>

class Game; //TBI

void main()
{
	//Create game object used to play the game
	Game game;

	//Test that numbers are not repeated
	assert(game.play(1, 2, 3, 4, 5, 6) == true); //Should Pass
	assert(game.play(7, 8, 9, 10, 11, 12) == true); //Should Pass
	assert(game.play(1, 2, 3, 4, 4, 4) == false); //Should Fail
	assert(game.play(1, 1, 1, 2, 3, 4) == false); //Should Fail

	//Test that numbers are between 1-46
	assert(game.play(0, 2, 3, 4, 5, 6) == false); //Should Fail due to 0
	assert(game.play(1, 2, 3, 4, 5, 46) == false); //Should Pass
	assert(game.play(1, 2, 3, 4, 5, 47) == false); //Should Fail due to 47
}