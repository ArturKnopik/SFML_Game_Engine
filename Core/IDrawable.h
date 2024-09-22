#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "export.h"

#include <memory>

namespace kod {

class IDrawable
{
public:
	KOD_API IDrawable() = default;
	KOD_API virtual void draw(sf::RenderWindow &window) = 0;
};
} // namespace kod
