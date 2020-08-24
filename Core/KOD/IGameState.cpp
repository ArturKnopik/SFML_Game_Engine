
#include <iostream>
#include "IGameState.h"
#include "UtilityTools.h"

KOD::IGameState::IGameState()
{
  m_event = std::make_shared<sf::Event>();
}

void KOD::IGameState::draw()
{
  //TODO:: implement search object in camera area to draw
  for (auto& obj : m_globalGameObjectMap) {
    auto objDrawable = obj.second->getDrawable();
    if (objDrawable != nullptr)
    {
      objDrawable->draw(m_game.lock()->m_window);
    }
  }
}

void KOD::IGameState::update(const int dt)
{
  for (auto& obj : m_globalGameObjectMap) {
    auto objUpdatable = obj.second->getUpdatable();
    if (objUpdatable != nullptr)
    {
      objUpdatable->update(dt);
    }

    auto objDrawable = obj.second->getDrawable();
    if (objDrawable != nullptr)
    {
      objDrawable->getAnimationController().update(dt);
    }

  }
}

void KOD::IGameState::input()
{
}

bool KOD::IGameState::addGameObject(std::shared_ptr<IGameObject> object)
{
  if (object)
  {
    m_globalGameObjectMap.insert(std::make_pair(object->getUid(), object));
    return true;
  }
  return false;
}

bool KOD::IGameState::removeGameObject(std::shared_ptr<IGameObject> object)
{
  if (object == nullptr)
  {
    return false;
  }
  auto objectToRemove = m_globalGameObjectMap.find(object->getUid());
  m_globalGameObjectMap.erase(objectToRemove);
  return true;
}

bool KOD::IGameState::removeGameObject(size_t uid)
{
  return false;
}
