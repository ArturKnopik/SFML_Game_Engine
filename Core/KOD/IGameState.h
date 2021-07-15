#pragma once
#include "KOD_export.h"
#include "Game.h"
#include "Camera.h"
#include "IGameObject.h"
#include <unordered_map>

namespace KOD
{
  class KOD_API IGameState {
  private:
    bool isObjectInLocalArea(const sf::Vector2f position, const sf::Vector2f additionalSpace, 
                                                          const std::shared_ptr<IGameObject> gameObject);
    sf::Vector2f m_additionalSpaceToScan;
  protected:
    std::shared_ptr<sf::Event> m_event;
    std::weak_ptr<Game> m_game;
    Camera m_camera;
    std::unordered_map<size_t, std::shared_ptr<IGameObject>> m_globalGameObjectMap;
    std::unordered_map<size_t, std::shared_ptr<IGameObject>> m_localObjectMap;
    void getLocalAreaObjectList(const sf::Vector2f position, const sf::Vector2f additionalSpace);
    void setAdditionalSpaceToSet(sf::Vector2f additionalSpace);
  public:
    IGameState();
    virtual ~IGameState() = default;
    virtual void draw();
    virtual void update(const size_t dt);
    virtual void input();
    bool addGameObject(std::shared_ptr<IGameObject> object);
    bool removeGameObject(std::shared_ptr<IGameObject> object);
    bool removeGameObject(size_t uid);
	const size_t getLocalAreaCount() const;
	const size_t getGlobalAreaCount() const;
    //[Type] getObjectFactory();

  };
}

