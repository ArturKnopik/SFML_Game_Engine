#include "ObjectFactory.h"

KOD::ObjectFactory::ObjectFactory()
{
}

void KOD::ObjectFactory::switchGameState(std::weak_ptr<IGameState> gameState)
{
  m_gameState = gameState;
}

KOD::ObjectFactory& KOD::ObjectFactory::getSingleton()
{
  static ObjectFactory singleton;
  return singleton;
}

bool KOD::ObjectFactory::addGameObject(std::shared_ptr<IGameObject> gameObject)
{
  if (!m_gameState.expired())
  {
    return m_gameState.lock()->addGameObject(gameObject);
  }
  return false;
}

