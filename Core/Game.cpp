#include "Game.h"

#include "DefinesUtil.h"

#include <SFML/System/Clock.hpp>
#include <iostream>

kod::Game& kod::Game::getInstance()
{
	static Game instance;
	return instance;
}

kod::Game::Game()
{
	// TODO: hardcoded
	/*
	sf::ContextSettings sfmlSettings;
	sfmlSettings.antialiasingLevel = 8;
	sf::Style::None - style without border
	*/
	m_window.create(sf::VideoMode(800, 600), "Default app name" /*, sf::Style::Default, sfmlSettings*/);
	m_window.setFramerateLimit(60);
}

kod::Game::~Game() {}

kod::Error kod::Game::gameLoop()
{
	auto state = currentState();
	if (!state) {
		return kod::Error::MEMORY;
	}

	kod::Error err = kod::Error::OK;

	while (err == kod::Error::OK && m_isRunning == true) {
		sf::Clock clock;
		while (m_window.isOpen()) {
			sf::Time elapsed = clock.restart();
			size_t dt = static_cast<uint64_t>(elapsed.asMicroseconds());
			if (currentState()) {
				m_window.clear();
				err = currentState()->update(dt);
				GOTO_END_ON_ERROR(err);
				err = currentState()->draw();
				GOTO_END_ON_ERROR(err);
				m_window.display();
			}
		}
	}
end:
	return err;
}

kod::Error kod::Game::handleWindowEvent()
{
	kod::Error err = kod::Error::OK;
	sf::Event evt;
	while (m_window.pollEvent(evt)) {
		std::cout << evt.type << std::endl;
		switch (evt.type) {
			case sf::Event::Closed:
				m_window.close();
				m_isRunning = false;
				break;
		}
		err = currentState()->draw();
		GOTO_END_ON_ERROR(err);
	}
end:
	return err;
}

KOD_API kod::Error kod::Game::pushState(std::shared_ptr<kod::IState> state) { return m_stateManager.pushState(state); }

KOD_API kod::Error kod::Game::popState() { return m_stateManager.popState(); }

KOD_API std::shared_ptr<kod::IState> kod::Game::currentState() { return m_stateManager.currentState(); }

sf::RenderWindow& kod::Game::getRenderWindow() { return m_window; }

kod::Error kod::Game::run()
{
	m_isRunning = true;

	return gameLoop();
}

kod::Error kod::Game::stop()
{
	m_isRunning = false;
	return kod::Error::OK;
}
