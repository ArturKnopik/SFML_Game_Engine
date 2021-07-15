#pragma once
#include "KOD_export.h"

namespace KOD
{
  class IUpdatable
  {
  public:
    IUpdatable() = default;
    virtual void update(const size_t dt) = 0;
  };
}

