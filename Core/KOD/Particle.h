#include "KOD_export.h"
#include "IGameObject.h"
#include <vector>


namespace KOD
{
  class ParticleEmiter;

  class KOD_API Particle
    :public IGameObject
  {
    size_t m_tickToRemove= 500000;
    size_t m_currenttickToRemove=0;
  public:
    Particle() = delete;
    Particle(size_t tickToRemove, std::shared_ptr<IUpdatable> updatable, std::shared_ptr<IDrawable> drawable);
    bool isExpired();
  };

  class IParticleController
  {
    size_t m_timeBetweneEmit = 500000;
    size_t m_currenttimeBetweneEmit = 0;
    //ParticleEmiter& m_particleEmiter;
  public:
    IParticleController();
    virtual ~IParticleController() = default;
    void emitParticle();
    bool checkTimeBetweeneEmit();
  };

  class KOD_API ParticleEmiter
  {
    size_t m_maxParticleToEmit = 0;
    std::vector<std::shared_ptr<Particle>> m_particleList;
    std::unique_ptr<IParticleController> m_particleController;
  public:
    ParticleEmiter(std::unique_ptr<IParticleController> particleController, size_t maxParticleToEmit);
    virtual void update(const int dt);
    virtual void draw(std::shared_ptr<sf::RenderWindow> window);
  };



}