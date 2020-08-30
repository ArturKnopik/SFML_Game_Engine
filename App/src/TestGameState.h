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
  void checkCollision();
  bool compareObjectUid(std::shared_ptr<KOD::IGameObject> left, std::shared_ptr<KOD::IGameObject> right);
public:
  TestGameState() = delete;
  TestGameState(std::shared_ptr<KOD::Game> game);
  virtual void input() override;
  virtual void update(const int dt) override;
  virtual ~TestGameState();
};

