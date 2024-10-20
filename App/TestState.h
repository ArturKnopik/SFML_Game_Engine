#pragma once
#include "IState.h"
#include "SampleParticle.h"

#include <Button.h>
#include <Label.h>
#include <Logger.h>
#include <Particle.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <ECS.h>

class TestState : public kod::IState
{
public:
	TestState(kod::Game& game);
	virtual void draw() override;
	virtual void update(const size_t dt) override;
	virtual void input(sf::Event& event) override;

private:
	void loadResources();
	void loadTextures();
	void loadFonts();

	// TODO: remove
	sf::Sprite m_sprite1;
	sf::Sprite m_sprite2;
	kod::ParticleEmiter<SampleParticle> m_particleEmiter;

	sf::RectangleShape m_particleRect;

	sf::Clock m_clock;
	sf::Time m_previousTime = sf::Time::Zero;
};
