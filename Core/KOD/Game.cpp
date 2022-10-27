#include "Game.h"
#include "IState.h"
#include "Settings.h"
#include "KOD/ResourceManager.h"
#include <iostream>

KOD::Game::Game()
{
	KOD::Settings settings;
	sf::ContextSettings sfmlSettings;
	sfmlSettings.antialiasingLevel = 8;
	//sf::Style::None - style without border
	m_window.create(sf::VideoMode(settings.windowsSizeX, settings.windowsSizeY), "Default app name", sf::Style::Default, sfmlSettings);
	m_window.setFramerateLimit(settings.FPS);
}

KOD::Game::Game(const KOD::Settings settings)
{
	sf::ContextSettings sfmlSettings;
	sfmlSettings.antialiasingLevel = 8;
	//sf::Style::None - style without border
	m_window.create(sf::VideoMode(settings.windowsSizeX, settings.windowsSizeY), settings.name, sf::Style::Default, sfmlSettings);
	m_window.setFramerateLimit(settings.FPS);
}

void KOD::Game::pushState(std::shared_ptr<KOD::IState> state)
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

std::shared_ptr<KOD::IState> KOD::Game::currentState()
{
	if (!m_states.empty())
	{
		return m_states.back();
	}
	return nullptr;
}

KOD::Game::~Game()
{
	while (!m_states.empty())
	{
		popState();
	}
	KOD::ResourceManager::getInstance().clean();
}

void KOD::Game::gameLoop()
{
	sf::Clock clock;
	while (m_window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		size_t dt = static_cast<int>(elapsed.asMicroseconds());
		if (currentState())
		{
			m_window.clear();
			currentState()->input();
			currentState()->update(dt);
			currentState()->draw();
			m_window.display();
		}
	}
}

sf::RenderWindow& KOD::Game::getRenderWindow()
{
	return m_window;
}
