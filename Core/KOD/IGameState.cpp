
#include <iostream>
#include "IGameState.h"
#include "UtilityTools.h"

KOD::IGameState::IGameState()
{
  m_event = std::make_shared<sf::Event>();
}

void KOD::IGameState::draw()
{
  sf::RectangleShape rect;
  rect.setFillColor(sf::Color::Red);
  rect.setSize({ 32, 32 });
  rect.setPosition({ 499, 600 });
  m_game.lock()->m_window->draw(rect);



  sf::View view;
  view.setSize(m_game.lock()->m_window->getSize().x, m_game.lock()->m_window->getSize().y);
  view.setCenter(m_camera.getPosition());
  m_game.lock()->m_window->setView(view);
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
  m_camera.updateCamera();
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
