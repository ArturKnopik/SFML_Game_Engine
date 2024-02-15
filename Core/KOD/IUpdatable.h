#pragma once
#include "KOD_export.h"

namespace KOD {
class KOD_API IUpdatable
{
public:
	IUpdatable() = default;
	virtual void update(const size_t dt) = 0;
};
} // namespace KOD
