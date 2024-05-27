#pragma once
#include "export.h"

namespace kod {

class KOD_API IUpdatable
{
public:
	IUpdatable() = default;
	virtual void update(const size_t dt) = 0;
};

} // namespace kod
