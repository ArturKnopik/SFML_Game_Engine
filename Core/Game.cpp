#include "Game.h"

#include "DefinesUtil.h"
#include "Logger.h"
#include "ResourceManager.h"

#include <SFML/System/Clock.hpp>

kod::Game::Game()
{
	// TODO: hardcoded
	/*
	sf::ContextSettings sfmlSettings;
	sfmlSettings.antialiasingLevel = 8;
	sf::Style::None - style without border
	*/
	m_window.create(sf::VideoMode({1500, 900}), "Default app name" /*, sf::Style::Default, sfmlSettings*/);
	// m_window.setFramerateLimit(60);
	m_sheduler.start();
}

kod::Game::Game(const char* appName)
{
	// TODO: hardcoded
	/*
	sf::ContextSettings sfmlSettings;
	sfmlSettings.antialiasingLevel = 8;
	sf::Style::None - style without border
	*/
	m_window.create(sf::VideoMode({1500, 900}), appName /*, sf::Style::Default, sfmlSettings*/);
	// m_window.setFramerateLimit(60);
	m_sheduler.start();
}

kod::Game::~Game() {}

void kod::Game::gameLoop()
{
	if (!m_stateManager.currentState()) {
		m_window.close();
		g_logger.log(kod::Logger::LogSeverity::ERROR, "There is no state object in the list, stoping!");
		return;
	}

	sf::Clock clock;
	while (m_window.isOpen() && m_isRunning == true) {
		sf::Time elapsed = clock.restart();
		size_t dt = static_cast<uint64_t>(elapsed.asMicroseconds());
		m_window.clear();
		m_sheduler.executeTasks();
		handleEvents();
		currentState()->update(dt);
		currentState()->updateGui(dt);
		currentState()->draw();
		currentState()->drawGui();
		m_window.display();
	}

	cleanup();
}

void kod::Game::handleEvents()
{
	while (const std::optional event = m_window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			m_window.close();
		} else if (const auto* resize = event->getIf<sf::Event::Resized>()) {
			sf::FloatRect visibleArea({0, 0}, {static_cast<float>(resize->size.x), static_cast<float>(resize->size.y)});
			m_window.setView(sf::View(visibleArea));
		}

		currentState()->input(event);
		currentState()->inputGui(event);
	}
	currentState()->input();
}

KOD_API void kod::Game::pushState(std::shared_ptr<kod::IState> state) { m_stateManager.pushState(state); }

KOD_API void kod::Game::popState() { return m_stateManager.popState(); }

KOD_API std::shared_ptr<kod::IState> kod::Game::currentState() { return m_stateManager.currentState(); }

sf::RenderWindow& kod::Game::getRenderWindow() { return m_window; }

void kod::Game::run()
{
	m_isRunning = true;
	gameLoop();
}

void kod::Game::stop()
{
	m_isRunning = false;
	m_sheduler.stop();
	m_sheduler.join();
}

kod::ResourceManager& kod::Game::getResourceManager() { return m_resourceManager; }

kod::Scheduler& kod::Game::getSheduler() { return m_sheduler; }

void kod::Game::cleanup()
{
	if (m_window.isOpen()) {
		m_window.close();
	}
}