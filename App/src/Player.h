#pragma once

#include <KOD/IGameObject.h>
#include "KOD/Animation.h"

class Player
  :public KOD::IGameObject
{
  KOD::Animation m_animation;
public:
  Player();
  virtual ~Player() = default;
 
};

