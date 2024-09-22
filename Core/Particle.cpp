#include "Particle.h"

bool kod::Particle::isAlive() { return m_isAlive; }

void kod::Particle::isAlive(bool alive) { m_isAlive = alive; }

void kod::Particle::update(size_t dt) {}

void kod::Particle::onSpawn(sf::Vector2f emiterPos) {}

void kod::Particle::draw(sf::RenderWindow& window) {}

void kod::Particle::setMaxLifeTime(size_t lifeTime) { m_maxAliveTime = lifeTime; }

size_t kod::Particle::getMaxLifeTime() { return m_maxAliveTime; }

size_t kod::Particle::getCurrentLifeTime() { return m_currentLifeTime; }

void kod::Particle::updateLifeTime(size_t dt)
{
	m_currentLifeTime += dt;
	if (getCurrentLifeTime() >= getMaxLifeTime()) {
		isAlive(false);
	}
}

void kod::Particle::reset()
{
	m_currentLifeTime = 0;
	isAlive(true);
}
