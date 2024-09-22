#include "SampleParticle.h"

#include "Const.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <random>

SampleParticle::SampleParticle()
{
	m_rect.setFillColor(sf::Color::Cyan);
	m_rect.setSize({2, 2});
}

void SampleParticle::setPosition(sf::Vector2f positon) { m_position = positon; }

sf::Vector2f SampleParticle::getPosition() { return m_position; }

void SampleParticle::setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }

sf::Vector2f SampleParticle::getVelocity() { return m_velocity; }

void SampleParticle::onSpawn(sf::Vector2f emiterPos)
{
	reset();

	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<float> velocityX(-30.f, 30.f);
	static std::uniform_real_distribution<float> velocityY(-90.f, -60.f);
	static std::uniform_int_distribution<size_t> distLifeTime(kod::time::TIME_1S * 2, kod::time::TIME_1S * 7);

	setPosition(emiterPos);
	setVelocity({velocityX(gen), velocityY(gen)});
	setMaxLifeTime(distLifeTime(gen));

	m_rect.setFillColor(sf::Color(255, 255, 128, 255));
}

void SampleParticle::update(size_t dt)
{
	sf::Vector2f velocity = getVelocity();
	sf::Vector2f position = getPosition();

	position.x += (velocity.x * static_cast<float>(dt) / kod::time::TIME_1S);
	position.y += (velocity.y * static_cast<float>(dt) / kod::time::TIME_1S);

	setPosition(position);
	m_rect.setPosition(position);

	float lifeRatio = static_cast<float>(getCurrentLifeTime()) / static_cast<float>(getMaxLifeTime()) * 100 * 2.5;
	int r = static_cast<int>(255);
	int g = static_cast<int>(lifeRatio);
	m_rect.setFillColor(sf::Color(r, g, 0, 255));
}

void SampleParticle::draw(sf::RenderWindow& window) { window.draw(m_rect); }
