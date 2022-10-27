#pragma once
#include "KOD_export.h"
#include "Game.h"
#include "IObject.h"

#include <unordered_map>
#include <stdexcept>

namespace KOD
{
  class KOD_API IState {
  protected:
    std::weak_ptr<Game> m_game;
  public:
    IState() = delete;
    IState(std::shared_ptr<KOD::Game> game);
    virtual ~IState() = default;
    virtual void draw() = 0;
    virtual void update(const size_t dt) = 0;
    virtual void input() = 0;
  };
}

