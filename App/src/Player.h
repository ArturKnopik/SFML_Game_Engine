#pragma once

#include <KOD/IGameObject.h>
#include "KOD/Animation.h"

class Player
  :public KOD::IGameObject
{
  KOD::Animation m_animation;
public:
  Player() = delete;
  Player(std::shared_ptr<KOD::IDrawable> drawing);
  virtual ~Player() = default;
  void update(const int dt);
};

