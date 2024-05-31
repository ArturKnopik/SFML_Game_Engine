#pragma once
#include "Error.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "export.h"

#include <memory>

namespace kod {

class IDrawable
{
public:
	KOD_API IDrawable() = default;
	KOD_API virtual kod::Error draw(sf::RenderWindow &window) = 0;
};
} // namespace kod
