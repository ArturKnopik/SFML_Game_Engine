#pragma once
#include "ICollider.h"
#include "IDrawable.h"
#include "IUpdatable.h"
#include "export.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

#include <iostream>
#include <memory>

namespace kod {

class KOD_API IObject
{
public:
	IObject();
	virtual ~IObject() = default;
	const size_t getUid() const;

private:
	static size_t sm_uid; // do not touch
	size_t m_uid;
};
} // namespace KOD
