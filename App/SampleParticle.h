#pragma once

#include <Particle.h>
#include <SFML/Graphics/RectangleShape.hpp>

class SampleParticle : public kod::Particle
{
public:
	SampleParticle();
	~SampleParticle() = default;
	void setPosition(sf::Vector2f positon);
	sf::Vector2f getPosition();

	void setVelocity(sf::Vector2f velocity);
	sf::Vector2f getVelocity();

	void onSpawn(sf::Vector2f emiterPos) override;
	void update(size_t dt) override;
	void draw(sf::RenderWindow& window) override;

private:
	sf::Vector2f m_position = {0.0, 0.0};
	sf::Vector2f m_velocity = {0.0, 0.0};
	sf::RectangleShape m_rect;
};
