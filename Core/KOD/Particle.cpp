#include "Particle.h"

KOD::Particle::Particle(size_t tickToRemove, std::shared_ptr<IUpdatable> updatable, std::shared_ptr<IDrawable> drawable)
  : IGameObject(updatable, drawable, nullptr), m_tickToRemove(tickToRemove)
{
}


bool KOD::Particle::isExpired()
{
  if (m_tickToRemove == 0)
  {
    return true;
  }
  return false;
}



KOD::IParticleController::IParticleController()
{
}

void KOD::IParticleController::emitParticle()
{

}

bool KOD::IParticleController::checkTimeBetweeneEmit()
{
  if (m_timeBetweneEmit < m_currenttimeBetweneEmit)
  {
    return false;
  }
  return false;
}

KOD::ParticleEmiter::ParticleEmiter(std::unique_ptr<IParticleController> particleController, size_t maxParticleToEmit)
  :m_particleController(std::move(particleController)), m_maxParticleToEmit(maxParticleToEmit)
{
}

void KOD::ParticleEmiter::update(const int dt)
{

  if (m_particleList.size() < m_maxParticleToEmit - 1)
  {
    if (m_particleController->checkTimeBetweeneEmit())
    {
      m_particleController->emitParticle();
    }
  }

  for (auto& iter : m_particleList)
  {
    auto iterUpdatable = iter->getUpdatable();
    if (iterUpdatable)
    {
      iterUpdatable->update(dt);
    }
  }
}

void KOD::ParticleEmiter::draw(std::shared_ptr<sf::RenderWindow> window)
{
  for (auto& iter : m_particleList)
  {
    auto iterDrawable = iter->getDrawable();
    if (iterDrawable)
    {
      iterDrawable->draw(window);
    }
  }
}
