#include "IUpdatable.h"
#include "ISolid.h"

const sf::Vector2f KOD::ISolid::getSize()
{
  return m_size;
}

void KOD::ISolid::setSize(sf::Vector2f size)
{
  m_size = size;
}

const sf::Vector2f KOD::ISolid::getCenter()
{
  return m_center;
}

void KOD::ISolid::setCenter(sf::Vector2f center)
{
  m_center = center;
}

void KOD::ISolid::updateView()
{
  m_view.setCenter(m_center);
}

const sf::View KOD::ISolid::getView()
{
  return m_view;
}
