#include "Player.h"
#include "KOD/ResourceManager.h"
#include "KOD/UtilityTools.h"
Player::Player(std::shared_ptr<KOD::IDrawable> drawing)
  :IGameObject(nullptr, drawing, nullptr)
{ 
  m_animation.setTexture(KOD::ResourceManager::getInstance().getTexture("playerSpaceShip"));
  m_animation.addFrame(KOD::Frame(sf::IntRect(0, 0, 34, 41), 500));
  //sf::IntRect(0, 0, 34, 41), 500) coords in imagea and animation time
  m_animation.addFrame(KOD::Frame(sf::IntRect(0, 41, 34, 41), 500));
  m_animation.addFrame(KOD::Frame(sf::IntRect(0, 82, 34, 41), 500));
  m_animation.addFrame(KOD::Frame(sf::IntRect(0, 123, 34, 41), 500));
  getDrawable()->getAnimationController().setAnimation(m_animation);
  getDrawable()->getAnimationController().play();
}

void Player::update(const int dt)
{
}
