#pragma once
#include "KOD_export.h"
#include "SFML/Graphics/Rect.hpp"
#include <vector>
namespace KOD
{
	class KOD_API Frame
	{
		int m_timeToNextFrame = 100000;
		sf::IntRect m_imagePosition;
	public:
		Frame() = delete;
		Frame(sf::IntRect imagePosition, int timeToNextFrame = 10000);
		const double getMaxFrameTime() const;
		const sf::IntRect getFrameRect() const;
	};
}
