#include "Game.h"

int main()
{
	Game* game = new Game();
	game->loop();
	delete game;

	return 0;
}