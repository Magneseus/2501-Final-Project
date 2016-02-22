#include "Game.h"

#include <iostream>

int main()
{
	std::cout << "START" << std::endl;

	Game* game = new Game();
	game->loop();
	delete game;

	std::cout << "END" << std::endl;

	return 0;
}