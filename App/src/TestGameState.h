#pragma once
#include <KOD/IState.h>
#include "Player.h"

class TestGameState :
  public KOD::IState
{
private:
  std::shared_ptr<Player> m_player;
  std::shared_ptr<Player> m_player2;
  sf::Event m_event;
  void printTestMassage();
  void checkCollision();
  //bool compareObjectUid(std::shared_ptr<KOD::IGameObject> left, std::shared_ptr<KOD::IGameObject> right);
public:
  TestGameState() = delete;
  TestGameState(std::shared_ptr<KOD::Game> game);
  virtual void draw() override {};
  virtual void input() override;
  virtual void update(const size_t dt) override;
  virtual ~TestGameState();
};

