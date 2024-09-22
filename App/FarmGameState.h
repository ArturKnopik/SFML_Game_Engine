#pragma once
#include "IState.h"
#include "Map.h"
#include "SampleParticle.h"

#include <ItemType.h>
#include <Logger.h>
#include <Particle.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

class FarmGameState : public kod::IState
{
public:
	FarmGameState(kod::Game& game);
	virtual void draw() override;
	virtual void update(const size_t dt) override;

private:
	void loadResources();
	void loadTextures();
	void loadMaps();
	void switchCurrentMap(std::string_view mapName);

	ItemTypeManager m_itemTypeManager;
	std::unordered_map<std::string, std::shared_ptr<Map>> m_maps;
	std::shared_ptr<Map> m_currentMap;

	// TODO: remove
	sf::Sprite m_sprite1;
	sf::Sprite m_sprite2;
	kod::ParticleEmiter<SampleParticle> m_particleEmiter;

	sf::RectangleShape m_particleCircle;

	sf::Clock m_clock;
	sf::Time m_previousTime = sf::Time::Zero;
};
