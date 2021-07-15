#include "IGameObject.h"

size_t KOD::IGameObject::sm_uid = 0;

KOD::IGameObject::IGameObject()
  :m_uid((sm_uid++))
{

}

KOD::IGameObject::IGameObject(std::shared_ptr<IUpdatable> updatable, std::shared_ptr<IDrawable> drawable, std::shared_ptr<Collider> solid)
  : m_updatable(updatable), m_drawable(drawable), m_collider(solid), m_uid((sm_uid++))
{
}

void KOD::IGameObject::setPosition(const sf::Vector2f position)
{
  m_position = position;
}

void KOD::IGameObject::setPosition(const int positionX, const int positionY)
{
  m_position.x = static_cast<float>(positionX);
  m_position.y = static_cast<float>(positionY);
}

const sf::Vector2f KOD::IGameObject::getPosition() const
{
  return m_position;
}

std::shared_ptr<KOD::IUpdatable> KOD::IGameObject::getUpdatable()
{
  if (m_updatable != nullptr)
  {
    return m_updatable;
  }
  return nullptr;
}

std::shared_ptr<KOD::IDrawable> KOD::IGameObject::getDrawable()
{
  if (m_drawable!= nullptr)
  {
    return m_drawable;
  }
  return nullptr;
}

const std::shared_ptr<KOD::Collider> KOD::IGameObject::getCollider() const
{
  if (m_collider != nullptr)
  {
    return m_collider;
  }
  return nullptr;
}

void KOD::IGameObject::onCollision(KOD::IGameObject_prt other)
{

}

const size_t KOD::IGameObject::getUid() const
{
  return m_uid;
}
