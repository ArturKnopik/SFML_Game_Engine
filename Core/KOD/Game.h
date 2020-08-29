#pragma once
#include "KOD_export.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>
#include <utility>

namespace KOD
{
  class IGameState;
  struct Settings;

  class KOD_API Game
  {
  private:
    std::vector<std::shared_ptr<IGameState>> m_states;
  public:
    Game();
    Game(const KOD::Settings settings);
    ~Game();
    void pushState(std::shared_ptr<IGameState> state);
    void popState();
    std::shared_ptr<IGameState> currentState();
    void gameLoop();
    std::shared_ptr<sf::RenderWindow> m_window;
  };
}
