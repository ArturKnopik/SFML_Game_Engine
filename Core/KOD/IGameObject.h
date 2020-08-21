#pragma once
#include "KOD_export.h"
#include "IUpdatable.h"
#include "IDrawable.h"
#include "ISolid.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <memory>
#include <iostream>


namespace KOD {
  class KOD_API IGameObject
  {
  private:
    static size_t sm_uid;
    size_t m_uid;
    sf::Vector2f m_size;
  protected:
    bool m_collisionable = false;
    int m_life = 1;
    sf::Vector2f m_position;
    sf::Sprite m_sprite;
    std::shared_ptr<IUpdatable> m_updatable;
    std::shared_ptr<IDrawable> m_drawable;
    std::shared_ptr<ISolid> m_solid;
  public:
    IGameObject();
    IGameObject(std::shared_ptr<IUpdatable> updatable, std::shared_ptr<IDrawable> drawable, std::shared_ptr<ISolid> m_solid); 
    virtual ~IGameObject() = default;
    const size_t getUid();
    void setPosition(const sf::Vector2f position);
    void setPosition(const int positionX, const int positionY);
    const sf::Vector2f getPosition();   
    std::shared_ptr<IUpdatable> getUpdatable();
    std::shared_ptr<IDrawable> getDrawable();
    std::shared_ptr<ISolid> getSolid();
  };
}
