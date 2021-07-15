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
    virtual void updateAnimation(const size_t dt);
  public:
    virtual void draw(sf::RenderWindow &window);
	void setPosition(sf::Vector2f position);
    AnimationController& getAnimationController();
  };
}

