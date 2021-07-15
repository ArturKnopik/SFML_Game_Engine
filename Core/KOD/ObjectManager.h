#pragma once
#include "KOD_export.h"
#include "IGameState.h"

namespace KOD
{
  class KOD_API ObjectManager
  {
  private:
    std::weak_ptr<IGameState> m_gameState;
    //
  public:
    ObjectManager();
    void switchGameState(std::weak_ptr<IGameState> gameState);
    //ObjectFactory(IGameState * gameState);
    static ObjectManager& getSingleton();
    bool addGameObject(std::shared_ptr<IGameObject> gameObject);
  };
}



