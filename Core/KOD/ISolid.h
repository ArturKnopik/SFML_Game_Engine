#pragma once
#include "KOD_export.h"
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\View.hpp"

namespace KOD
{
  class KOD_API ISolid
  {
    sf::Vector2f m_size;
    sf::Vector2f m_center;
    sf::View m_view;
  public:
    ISolid() = default;
    virtual void update(const float dt) = 0; 
    const sf::Vector2f getSize();
    void setSize(sf::Vector2f size);
    const sf::Vector2f getCenter();
    void setCenter(sf::Vector2f size);
    void updateView();
    const sf::View getView();
  };
}



