#pragma once
#include "KOD/IUpdatable.h"
#include "SFML/System/Vector2.hpp"

class PlayerUpdatable
  : public KOD::IUpdatable
{
private:
  enum Direction { STOP = 0, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4 };
  Direction m_currentDir = Direction::STOP;
  sf::Vector2f& m_position;
public:
  PlayerUpdatable() = delete;
  PlayerUpdatable(sf::Vector2f& positionReference);
  virtual void update(const int dt);
  void move(Direction dir);
};

