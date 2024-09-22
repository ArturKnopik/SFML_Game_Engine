#pragma once

#include "Const.h"
#include "GameObject.h"
#include "export.h"

#include <functional>
#include <stack>
#include <type_traits>


namespace kod {

class Particle
{
public:
	KOD_API Particle() = default;
	KOD_API virtual ~Particle() = default;

	KOD_API bool isAlive();
	KOD_API void isAlive(bool isAlive);

	KOD_API virtual void update(size_t dt);
	KOD_API virtual void onSpawn(sf::Vector2f emiterPos);
	KOD_API virtual void draw(sf::RenderWindow& window);

	KOD_API void setMaxLifeTime(size_t lifeTime);
	KOD_API size_t getMaxLifeTime();
	KOD_API size_t getCurrentLifeTime();
	KOD_API void updateLifeTime(size_t dt);

	KOD_API void reset();

private:
	bool m_isAlive = false;
	size_t m_maxAliveTime = kod::time::TIME_1S; // 1s
	size_t m_currentLifeTime = 0;
};

template <typename T>
class ParticleEmiter : public kod::GameObject
{
public:
	ParticleEmiter();
	~ParticleEmiter() = default;
	ParticleEmiter(size_t particleCount);
	void update(size_t dt) override;
	void draw(sf::RenderWindow& window) override;
	void shouldSpawnParticles(bool shouldSpawnParticles);
	void setTimeBetweenParticleSpawn(size_t timeBetweenParticleSpawn);
	void maxSpawnedParticleAtOnce(size_t maxSpawnedParticleAtOnce);
	size_t getParticleCount();
	void setPosition(sf::Vector2f positon);

private:
	void internalInit();
	void spawnParticleIfCan();

	bool m_shouldSpawnParticles = true;

	size_t m_aliveParticlesCount = 0;
	size_t m_particleCount = 10;
	size_t m_timeBetweenParticleSpawn = 100;
	size_t m_spawnTimer = 0;
	size_t m_maxSpawnedParticleAtOnce = 1;

	std::vector<T> m_particleArray;
	std::stack<size_t> m_freeParticleIndex;

	sf::Vector2f m_position = {0.0, 0.0};
};

} // namespace kod

// TEMPLATE IMPLEMENTATION

template <typename T>
kod::ParticleEmiter<T>::ParticleEmiter()
{
	static_assert(std::is_base_of<kod::Particle, T>::value, "T must be derived from kod::Particle");
	internalInit();
}

template <typename T>
kod::ParticleEmiter<T>::ParticleEmiter(size_t particleCount) : m_particleCount(particleCount)
{
	internalInit();
}

template <typename T>
void kod::ParticleEmiter<T>::update(size_t dt)
{
	for (size_t i = 0; i < m_particleArray.size(); i++) {
		T& particle = m_particleArray[i];
		if (particle.isAlive()) {
			particle.update(dt);
			particle.updateLifeTime(dt);
			if (!particle.isAlive()) {
				m_freeParticleIndex.push(i);
				m_aliveParticlesCount--;
			}
		}
	}

	m_spawnTimer += dt;
	if (m_timeBetweenParticleSpawn == 0) {
		while (!m_freeParticleIndex.empty()) {
			spawnParticleIfCan();
		}
	} else if (m_spawnTimer >= m_timeBetweenParticleSpawn) {
		m_spawnTimer = 0;
		spawnParticleIfCan();
	}
}

template <typename T>
void kod::ParticleEmiter<T>::draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < m_particleArray.size(); i++) {
		T& particle = m_particleArray[i];
		if (particle.isAlive()) {
			particle.draw(window);
		}
	}
}

template <typename T>
void kod::ParticleEmiter<T>::shouldSpawnParticles(bool shouldSpawnParticles)
{
	m_shouldSpawnParticles = shouldSpawnParticles;
}

template <typename T>
void kod::ParticleEmiter<T>::setTimeBetweenParticleSpawn(size_t timeBetweenParticleSpawn)
{
	m_timeBetweenParticleSpawn = timeBetweenParticleSpawn;
}

template <typename T>
void kod::ParticleEmiter<T>::maxSpawnedParticleAtOnce(size_t maxSpawnedParticleAtOnce)
{
	m_maxSpawnedParticleAtOnce = maxSpawnedParticleAtOnce;
}

template <typename T>
size_t kod::ParticleEmiter<T>::getParticleCount()
{
	return m_aliveParticlesCount;
}

template <typename T>
void kod::ParticleEmiter<T>::setPosition(sf::Vector2f positon)
{
	m_position = positon;
}

template <typename T>
void kod::ParticleEmiter<T>::internalInit()
{
	m_particleArray.resize(m_particleCount);
	for (size_t i = 0; i < m_particleCount; i++) {
		m_freeParticleIndex.push(i);
	}
}

template <typename T>
void kod::ParticleEmiter<T>::spawnParticleIfCan()
{
	if (m_freeParticleIndex.empty()) {
		return;
	}

	for (size_t i = 0; i < std::min(m_maxSpawnedParticleAtOnce, m_freeParticleIndex.size()); i++) {
		size_t index = m_freeParticleIndex.top();
		T& particle = m_particleArray[index];
		particle.isAlive(true);
		particle.onSpawn(m_position);
		m_freeParticleIndex.pop();
		m_aliveParticlesCount++;
	}
}
