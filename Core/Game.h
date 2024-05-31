#pragma once

#include "StateManager.h"
#include "export.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace kod {

class Game
{
public:
	KOD_API static Game& getInstance();

	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;

	KOD_API kod::Error pushState(std::shared_ptr<kod::IState> state);
	KOD_API kod::Error popState();
	KOD_API std::shared_ptr<kod::IState> currentState();
	KOD_API sf::RenderWindow& getRenderWindow();
	KOD_API kod::Error run();
	KOD_API kod::Error stop();

private:
	Game();
	~Game();

	kod::Error gameLoop();
	kod::Error handleWindowEvent();
	StateManager m_stateManager;
	sf::RenderWindow m_window;
	bool m_isRunning = true;
};

} // namespace kod
