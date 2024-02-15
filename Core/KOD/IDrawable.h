#pragma once
#include "AnimationController.h"
#include "KOD_export.h"
#include "SFML/Graphics/RenderWindow.hpp"

#include <memory>

namespace KOD {
class KOD_API IDrawable
{
public:
	IDrawable() = default;
	virtual void draw(sf::RenderWindow &window) = 0;
};
} // namespace KOD
