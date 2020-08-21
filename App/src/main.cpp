#include <iostream>
#include <KOD/Game.h>
#include "MenuState.h"
int main()
{
  std::shared_ptr<KOD::Game> game=std::make_shared<KOD::Game>();
  std::shared_ptr<KOD::IGameState> menuState=std::make_shared<MenuState>(game);
  game->pushState(menuState);
  game->gameLoop();
  return 1;
}