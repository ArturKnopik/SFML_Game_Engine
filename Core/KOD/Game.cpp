#include "Game.h"
#include "IGameState.h"
#include "Settings.h"
#include "ObjectManager.h"
#include <iostream>
#include "KOD/ResourceManager.h"
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

void KOD::Game::pushState(std::shared_ptr<IGameState> state)
{
	if (state)
	{
		m_states.push_back(state);
		auto& objectFactory = ObjectManager::getSingleton();
		objectFactory.switchGameState(state);
	}
}

void KOD::Game::popState()
{
	if (!m_states.empty())
	{
		m_states.pop_back();
		auto& objectFactory = ObjectManager::getSingleton();
		if (!m_states.empty())
		{
			objectFactory.switchGameState(m_states.back());
		}
	}
}

KOD::Game::~Game()
{
	while (!m_states.empty())
	{
		popState();
	}
	KOD::ResourceManager::getInstance().clean();
}

std::shared_ptr<KOD::IGameState> KOD::Game::currentState()
{
	if (!m_states.empty())
	{
		return m_states.back();
	}
	return nullptr;
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
			currentState()->input();
			currentState()->update(dt);
			m_window.clear();
			currentState()->draw();
			m_window.display();
		}
	}
}

sf::RenderWindow& KOD::Game::getRenderWindow()
{
	return m_window;
}
