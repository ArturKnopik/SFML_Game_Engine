#pragma once
#include "export.h"
#include "SFML/Graphics/RenderWindow.hpp"

#include <memory>

namespace kod {

class KOD_API IDrawable
{
public:
	IDrawable() = default;
	virtual void draw(sf::RenderWindow &window) = 0;
};
} // namespace KOD
