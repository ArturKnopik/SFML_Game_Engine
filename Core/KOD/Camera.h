#pragma once
#include "KOD_export.h"
#include "IGameObject.h"
#include "SFML/System/Vector2.hpp"
#include <memory>
namespace KOD {
  class KOD_API Camera
  {
  private:
    sf::Vector2f m_position;
    std::shared_ptr<IGameObject> m_gameObejct;
  public:
    Camera();
    Camera(sf::Vector2f position);
    Camera(std::shared_ptr<IGameObject> gameObejct);
    const sf::Vector2f getPosition();
    void setPosition(sf::Vector2f position);
    void updateCamera();
    void bindGameObiect(std::shared_ptr<IGameObject> gameObejct);
    //TODO: add 
  };
}

