#pragma once

#include <KOD/IObject.h>
#include "KOD/Animation.h"

class Player
  :public KOD::IObject
{
  KOD::Animation m_animation;
public:
  Player();
  virtual ~Player() = default;
 
};

