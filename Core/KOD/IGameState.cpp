
#include <iostream>
#include "IGameState.h"
#include "UtilityTools.h"

void KOD::IGameState::getLocalAreaObjectList(sf::Vector2f position, sf::Vector2f additionalSpace = { 0,0 })
{
  m_localObjectMap.clear();
  sf::Vector2u screenSize = m_game.lock()->m_window->getSize();
  for (const auto& obj : m_globalGameObjectMap)
  {
    if (isObjectInLocalArea(position, additionalSpace, obj.second))
    {
      m_localObjectMap.insert({ obj.first ,obj.second });
    }
  }
}

void KOD::IGameState::setAdditionalSpaceToSet(sf::Vector2f additionalSpace)
{
  m_additionalSpaceToScan = additionalSpace;
}

bool KOD::IGameState::isObjectInLocalArea(const sf::Vector2f position, const sf::Vector2f additionalSpace,
  const std::shared_ptr<IGameObject> gameObject)
{
  sf::Vector2u windowSize = m_game.lock()->m_window->getSize();
  sf::Vector2f scanAreaPosition = sf::Vector2f{ position.x - (windowSize.x / 2) - additionalSpace.x,
                                   position.y - (windowSize.y / 2) - additionalSpace.y };

  sf::Vector2f windowAndOffsetSize = sf::Vector2f{ m_game.lock()->m_window->getSize().x + (2 * additionalSpace.x),
                                   m_game.lock()->m_window->getSize().y + (2 * additionalSpace.y) };
  sf::RectangleShape rect;
  rect.setPosition(scanAreaPosition);
  rect.setSize(windowAndOffsetSize);
  rect.setFillColor(sf::Color(255, 0, 0, 30));
  m_game.lock()->m_window->draw(rect);
  return collsionDetectionAABBPosByPos(scanAreaPosition, windowAndOffsetSize, gameObject->getPosition(), gameObject->getSize());
}


KOD::IGameState::IGameState()
{
  m_event = std::make_shared<sf::Event>();
}

void KOD::IGameState::draw()
{
  sf::View view;
  view.setSize(m_game.lock()->m_window->getSize().x, m_game.lock()->m_window->getSize().y);
  view.setCenter(m_camera.getPosition());
  m_game.lock()->m_window->setView(view);
  for (auto& obj : m_localObjectMap) {
    auto objDrawable = obj.second->getDrawable();
    if (objDrawable != nullptr)
    {
      objDrawable->draw(m_game.lock()->m_window);
    }
  }
}

void KOD::IGameState::update(const int dt)
{
  getLocalAreaObjectList(m_camera.getPosition(), m_additionalSpaceToScan);
  sendDebugInformation("## all objects: " + std::to_string(m_globalGameObjectMap.size()) + ", local area: " + std::to_string(m_localObjectMap.size()) + "\n");
  for (auto& obj : m_localObjectMap)
  {
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
  m_camera.updateCamera();
  sendDebugInformation(KOD::clearScreen(""));
}

void KOD::IGameState::input()
{
}

bool KOD::IGameState::addGameObject(std::shared_ptr<IGameObject> object)
{
  if (object == nullptr)
  {
    return false;
  }
  m_globalGameObjectMap.insert(std::make_pair(object->getUid(), object));
  return true;
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
  auto objectToRemove = m_globalGameObjectMap.find(uid);
  m_globalGameObjectMap.erase(objectToRemove);
  return true;
}
