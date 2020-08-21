#include "Camera.h"

KOD::Camera::Camera()
  :m_position({0,0}) // set camera central position to 0:0
{
}

KOD::Camera::Camera(sf::Vector2f position)
  :m_position(position)
{
}

KOD::Camera::Camera(std::shared_ptr<IGameObject> gameObejct)
  :m_gameObejct(gameObejct)
{
}

const sf::Vector2f KOD::Camera::getPosition()
{
  return m_position;
}

void KOD::Camera::setPosition(sf::Vector2f position)
{
  if (m_gameObejct != nullptr)
  {
    m_gameObejct = nullptr;
    m_position = position;
  }
  else
  {
    m_position = position;
  }
}

void KOD::Camera::updateCamera()
{
  if (m_gameObejct != nullptr)
  {
    m_position = m_gameObejct->getPosition();
  }
}

void KOD::Camera::bindGameObiect(std::shared_ptr<IGameObject> gameObejct)
{
  m_gameObejct = gameObejct;
}
