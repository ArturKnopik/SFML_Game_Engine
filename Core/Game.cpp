#include "Game.h"

#include "DefinesUtil.h"
#include "Logger.h"
#include "ResourceManager.h"

#include <SFML/System/Clock.hpp>

// Benchmark END : 5000 iterations took 15.720197 seconds. - 02.10.2024
#define BENCHMARK

kod::Game::Game()
{
	// TODO: hardcoded
	/*
	sf::ContextSettings sfmlSettings;
	sfmlSettings.antialiasingLevel = 8;
	sf::Style::None - style without border
	*/
	m_window.create(sf::VideoMode(1500, 900), "Default app name" /*, sf::Style::Default, sfmlSettings*/);
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
	m_window.create(sf::VideoMode(1500, 900), appName /*, sf::Style::Default, sfmlSettings*/);
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

#ifdef BENCHMARK
	size_t benchmark_iterations = 0;
	const size_t benchmark_iterationToExecute = 5000;
	auto start = std::chrono::high_resolution_clock::now();
	g_logger.log(kod::Logger::LogSeverity::FATAL, "Benchmark START");
#endif

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

#ifdef BENCHMARK
		benchmark_iterations++;
		if (benchmark_iterationToExecute == benchmark_iterations) {
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;
			g_logger.log(kod::Logger::LogSeverity::FATAL,
			             std::string("Benchmark END: " + std::to_string(benchmark_iterationToExecute) +
			                         " iterations took " + std::to_string(elapsed_seconds.count()) + " seconds.")
			                 .c_str());
		}
#endif
	}

	cleanup();
}

void kod::Game::handleEvents()
{
	sf::Event evt;
	while (m_window.pollEvent(evt)) {
		switch (evt.type) {
			case sf::Event::Closed:
				m_window.close();
				m_isRunning = false;
				m_sheduler.stop();
				break;
			case sf::Event::Resized:
				sf::FloatRect visibleArea(0, 0, static_cast<float>(evt.size.width),
				                          static_cast<float>(evt.size.height));
				m_window.setView(sf::View(visibleArea));
				break;
		}

		currentState()->input(evt);
		currentState()->inputGui(evt);
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