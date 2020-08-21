#pragma once
#include "KOD_export.h"
#include "Game.h"
#include "Camera.h"
#include "IGameObject.h"
#include <unordered_map>

namespace KOD
{
  class KOD_API IGameState {
  protected:
    std::shared_ptr<sf::Event> m_event;
    std::weak_ptr<Game> m_game;
    Camera m_camera;
    std::unordered_map<size_t, std::shared_ptr<IGameObject>> m_globalGameObjectMap;
    //std::unordered_map<size_t, std::shared_ptr<IGameObject>> m_localObjectMap;
  public:
    IGameState();
    virtual ~IGameState() = default;
    virtual void draw();
    virtual void update(const int dt);
    virtual void input();
    bool addGameObject(std::shared_ptr<IGameObject> object);
    bool removeGameObject(std::shared_ptr<IGameObject> object);
    bool removeGameObject(size_t uid);

  };
}

