#pragma once
#include "KOD_export.h"
#include "SFML/Graphics/Rect.hpp"

namespace KOD {

template <typename T>
class KOD_API FrameRect
{
	T left;   //!< Left coordinate of the rectangle
	T top;    //!< Top coordinate of the rectangle
	T width;  //!< Width of the rectangle
	T height; //!< Height of the rectangle
};

typedef FrameRect<uint32_t> IntRect;

class KOD_API Frame
{
private:
	int m_timeToNextFrame = 100000;
	IntRect m_imagePosition;

public:
	Frame() = delete;
	Frame(const IntRect &imagePosition, int timeToNextFrame = 10000);
	const double getMaxFrameTime() const;
	const IntRect getFrameRect() const;
};
} // namespace KOD
