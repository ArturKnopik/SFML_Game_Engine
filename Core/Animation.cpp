#include "Animation.h"

kod::Frame::Frame(sf::IntRect imagePosition, size_t time) :
    m_imagePosition(imagePosition), m_timeToNextFrame(time)
{}

const size_t kod::Frame::getDuration() const { return m_timeToNextFrame; }

const sf::IntRect kod::Frame::getFrameRect() const { return m_imagePosition; }

void kod::Frame::setTexture(std::shared_ptr<sf::Texture> texture) { m_texture = texture; }

const std::shared_ptr<sf::Texture> kod::Frame::getTexture() const { return m_texture; }

void kod::Animation::addFrame(kod::Frame frame) { m_frameList.push_back(frame); }

const kod::Frame& kod::Animation::getCurrentFrame() const
{
	return m_frameList[m_currentFrameIndex];
}

void kod::Animation::update(const size_t dt)
{
	// TODO: add synchronized case

	if (m_frameList.empty()) return;

	m_frameTime += dt;

	if (m_frameTime >= m_frameList[m_currentFrameIndex].getDuration()) {
		m_frameTime = 0;
		m_currentFrameIndex = (m_currentFrameIndex + 1) % m_frameList.size();
	}
}

void kod::Animation::reset()
{
	m_currentFrameIndex = 0;
	m_frameTime = 0;
}

void kod::Animation::isSynchronized(bool synchronized) { m_isSynchronized = synchronized; }

bool kod::Animation::isSynchronized() { return m_isSynchronized; }

bool kod::Animation::hasFrame() { return m_frameList.empty(); }