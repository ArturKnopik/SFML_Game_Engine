#include "ObjectManager.h"

KOD::ObjectManager::ObjectManager()
{
}

void KOD::ObjectManager::switchGameState(std::weak_ptr<IGameState> gameState)
{
  m_gameState = gameState;
}

KOD::ObjectManager& KOD::ObjectManager::getSingleton()
{
  static ObjectManager singleton;
  return singleton;
}

bool KOD::ObjectManager::addGameObject(std::shared_ptr<IGameObject> gameObject)
{
  if (!m_gameState.expired())
  {
    return m_gameState.lock()->addGameObject(gameObject);
  }
  return false;
}

