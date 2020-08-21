#include <iostream>
#include "Game.h"
#include "IGameState.h"
#include "Settings.h"

KOD::Game::Game()
{
  unsigned int sizeX = 1000, sizeY = 800;
  const std::string appName = "Default app name";
  sf::ContextSettings sfmlSettings;
  sfmlSettings.antialiasingLevel = 8;
  m_window = std::make_shared<sf::RenderWindow>();				//sf::Style::None - style without border
  m_window->create(sf::VideoMode(sizeX, sizeY), appName, sf::Style::Default, sfmlSettings);

}

KOD::Game::Game(KOD::Settings settings)
{
  sf::ContextSettings sfmlSettings;
  sfmlSettings.antialiasingLevel = 8;
  m_window = std::make_shared<sf::RenderWindow>();				//sf::Style::None - style without border
  m_window->create(sf::VideoMode(settings.windowsSizeX, settings.windowsSizeY), settings.name, sf::Style::Default, sfmlSettings);
  m_window->setFramerateLimit(settings.FPS);
}

void KOD::Game::pushState(std::shared_ptr<IGameState> state)
{
  if (state)
  {
    m_states.push_back(state);
  }
}

void KOD::Game::popState()
{
  if (!m_states.empty())
  {
    m_states.pop_back();
  }
}

KOD::Game::~Game()
{
  while (!m_states.empty())
  {
    popState();
  }
}

std::shared_ptr<KOD::IGameState> KOD::Game::currentState()
{
  if (m_states.empty())
  {
    return nullptr;
  }
  else
  {
    return m_states.back();
  }
}

void KOD::Game::gameLoop()
{
  sf::Clock clock;
  while (m_window->isOpen())
  {
    sf::Time elapsed = clock.restart();
    int dt = static_cast<int>(elapsed.asMicroseconds());
    currentState()->input();
    currentState()->update(dt);
    m_window->clear();
    currentState()->draw();
    m_window->display();
  }
}
