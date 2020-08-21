#pragma once
#include "KOD_export.h"

namespace KOD
{
  class IUpdatable
  {
  public:
    IUpdatable() = default;
    virtual void update(const int dt) = 0;
  };
}

