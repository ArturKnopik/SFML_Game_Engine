#include "IUpdatable.h"
#include "Solid.h"

KOD::Solid::Solid(sf::Vector2f& position, sf::Vector2f& size)
  :m_position(position), m_size(size)
{
}

const sf::Vector2f& KOD::Solid::getSize()
{
  return m_size;
}

void KOD::Solid::onCollsion()
{
}
