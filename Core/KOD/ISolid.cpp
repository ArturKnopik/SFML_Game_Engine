#include "IUpdatable.h"
#include "ISolid.h"

KOD::ISolid::ISolid(sf::Vector2f& position, sf::Vector2f& size)
  :m_position(position), m_size(size)
{
}
