#pragma once
#include <KOD/IGameState.h>
#include "Player.h"

class TestGameState :
  public KOD::IGameState
{
private:
  std::shared_ptr<Player> m_player;
  std::shared_ptr<Player> m_player2;
  void printTestMassage();
public:
  TestGameState() = delete;
  TestGameState(std::shared_ptr<KOD::Game> game);
  virtual void input() override;
  virtual ~TestGameState();
};

