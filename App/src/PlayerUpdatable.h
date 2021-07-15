#pragma once
#include "KOD/IUpdatable.h"
#include "SFML/System/Vector2.hpp"

class PlayerUpdatable
  : public KOD::IUpdatable
{
public: //TODO Ugly but work, fix this ;/
  enum class Direction {
    STOP = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
  };
private:
  Direction m_verticalDirection = Direction::STOP;
  Direction m_horizontalDirection = Direction::STOP;
  sf::Vector2f& m_position;
public:
  PlayerUpdatable() = delete;
  PlayerUpdatable(sf::Vector2f& position);
  virtual ~PlayerUpdatable() = default;
  virtual void update(const size_t dt) override;
  void setHorizontalDirection(Direction direction);
  void setVerticalDirection(Direction direction);
};
