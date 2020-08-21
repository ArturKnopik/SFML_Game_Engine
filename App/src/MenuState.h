#pragma once
#include <KOD/IGameState.h>
class MenuState :
  public KOD::IGameState
{
private:
public:
  MenuState() = delete;
  MenuState(std::shared_ptr<KOD::Game> game);
  virtual void input() override;
  virtual ~MenuState();
};

