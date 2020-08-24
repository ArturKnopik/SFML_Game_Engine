#include "PlayerUpdatable.h"

PlayerUpdatable::PlayerUpdatable(sf::Vector2f& positionReference)
  :m_position(positionReference)
{
}

void PlayerUpdatable::update(const int dt)
{
}

void PlayerUpdatable::move(Direction dir)
{
  m_currentDir = dir;
}
