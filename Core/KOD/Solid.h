#pragma once
#include "KOD_export.h"
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\View.hpp"

namespace KOD
{
  class KOD_API Solid
  {
    sf::Vector2f& m_size;
    sf::Vector2f& m_position;
  public:
    Solid() = delete;
    Solid(sf::Vector2f& position, sf::Vector2f& size);
    const sf::Vector2f& getSize();
    virtual void onCollsion();
  };
}



