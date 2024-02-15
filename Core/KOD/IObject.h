#pragma once
#include "ICollider.h"
#include "IDrawable.h"
#include "IUpdatable.h"
#include "KOD_export.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

#include <iostream>
#include <memory>

namespace KOD {
class KOD_API IObject
{
private:
	static size_t m_st_uid; // do not touch
	size_t m_uid;

public:
	IObject();
	virtual ~IObject() = default;
	const size_t getUid() const;
};
} // namespace KOD
