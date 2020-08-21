#include "MenuState.h"
#include "PlayerDrawing.h"
#include "Player.h"
#include "KOD/ResourceManager.h"

MenuState::MenuState(std::shared_ptr<KOD::Game> game)
{
  m_game = game;
  // START: TESTING PIECE OF CODE
  auto texture = std::make_shared<sf::Texture>();
  texture->loadFromFile("resource\\playerSpaceShip.png");
  KOD::ResourceManager::getInstance().addResource("playerSpaceShip", texture);

  auto player = std::make_shared<Player>(std::make_shared<PlayerDrawing>());
  addGameObject(player);
  player->getDrawable()->getAnimationController().play();
  // END TESTING PIECE OF CODE
}

void MenuState::input()
{
  IGameState::input();

  while (m_game.lock()->m_window->pollEvent(*m_event))
  {
    switch (m_event->type)
    {
    case sf::Event::Closed:
      m_game.lock()->m_window->close();
      break;

    case sf::Event::KeyPressed:
      if (m_event->key.code == sf::Keyboard::Escape)
      {
        // fast quit code - debug
        m_game.lock()->m_window->close();
      }
      break;
    }
  }
}


MenuState::~MenuState()
{
}
