#pragma once
#include "KOD_export.h"
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\View.hpp"

namespace KOD
{
  class KOD_API ISolid
  {
    sf::Vector2f& m_size;
    sf::Vector2f& m_position;
  public:
    ISolid() = delete;
    ISolid(sf::Vector2f& position, sf::Vector2f& size);
    virtual void onCollsion() = 0;
  };
}



