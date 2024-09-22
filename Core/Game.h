#pragma once

#include "Logger.h"
#include "ResourceManager.h"
#include "StateManager.h"
#include "export.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace kod {

class Game
{
public:
	KOD_API Game();
	KOD_API Game(const char* appName);
	KOD_API ~Game();

	KOD_API void pushState(std::shared_ptr<kod::IState> state);
	KOD_API void popState();
	KOD_API std::shared_ptr<kod::IState> currentState();

	KOD_API sf::RenderWindow& getRenderWindow();

	KOD_API void run();
	KOD_API void stop();
	KOD_API ResourceManager& getResourceManager();

private:
	void gameLoop();
	void handleEvents();
	StateManager m_stateManager;
	sf::RenderWindow m_window;
	bool m_isRunning = true;
	ResourceManager m_resourceManager;

	void cleanup();
};

} // namespace kod
