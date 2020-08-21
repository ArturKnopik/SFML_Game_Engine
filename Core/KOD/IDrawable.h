#pragma once
#include "KOD_export.h"
#include "AnimationController.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <memory>

namespace KOD
{
  class KOD_API IDrawable
  {
  private: 
    AnimationController m_animationController;
    sf::Sprite m_sprite;
    sf::Vector2f m_spritePosition;
    virtual void updateAnimation(const int dt);
  public:
    IDrawable() = default;
    virtual void draw(std::shared_ptr<sf::RenderWindow> window);
    AnimationController& getAnimationController();
  };
}

