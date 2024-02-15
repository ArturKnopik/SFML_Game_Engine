#include "TestGameState.h"

#include <KOD/Game.h>
#include <iostream>

int main()
{
	std::shared_ptr<KOD::Game> game = std::make_shared<KOD::Game>();
	std::shared_ptr<KOD::IState> menuState = std::make_shared<TestGameState>(game);
	game->pushState(menuState);
	game->gameLoop();
	return 0;
}