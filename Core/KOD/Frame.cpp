#include "Frame.h"


KOD::Frame::Frame(sf::IntRect imagePosition, int timeToNextFrameAsMs)
	:m_imagePosition(imagePosition), m_timeToNextFrame(timeToNextFrameAsMs * 1000)
{
}

const double KOD::Frame::getMaxFrameTime() const
{
	return m_timeToNextFrame;
}

const sf::IntRect KOD::Frame::getFrameRect() const
{
	return m_imagePosition;
}
