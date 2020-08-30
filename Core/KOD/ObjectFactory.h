#pragma once
#include "KOD_export.h"
#include "IGameState.h"

namespace KOD
{
  class KOD_API ObjectFactory
  {
  private:
    std::weak_ptr<IGameState> m_gameState;
    //
  public:
    ObjectFactory();
    void switchGameState(std::weak_ptr<IGameState> gameState);
    //ObjectFactory(IGameState * gameState);
    static ObjectFactory& getSingleton();
    void addGameObject(std::shared_ptr<IGameObject> gameObject);
  };
}



