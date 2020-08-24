#pragma once
#include <KOD/IGameState.h>
#include "Player.h"

class MenuState :
  public KOD::IGameState
{
private:
  std::shared_ptr<Player> m_player;
  void printTestMassage();
public:
  MenuState() = delete;
  MenuState(std::shared_ptr<KOD::Game> game);
  virtual void input() override;
  virtual ~MenuState();
};

