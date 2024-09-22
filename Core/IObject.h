#pragma once
#include "ICollider.h"
#include "IDrawable.h"
#include "IUpdatable.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "export.h"

#include <iostream>
#include <memory>

namespace kod {

class IObject
{
public:
	KOD_API IObject();
	KOD_API virtual ~IObject() = default;
	KOD_API const size_t getUid() const;

private:
	static size_t sm_uid; // do not touch
	size_t m_uid;
};
} // namespace kod
