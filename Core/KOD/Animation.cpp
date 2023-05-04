#include "Animation.h"


KOD::Animation::Animation()
{
}

KOD::Animation::~Animation()
{
	m_texture = nullptr;
}

void KOD::Animation::addFrame(KOD::Frame frame)
{
	m_frameList.push_back(frame);
}

void KOD::Animation::setTexture(std::shared_ptr<sf::Texture> texture)
{
	m_texture = texture;
}

const std::shared_ptr<sf::Texture> KOD::Animation::getTexture() const
{
	if (m_texture)
	{
		return m_texture;
	}
	return nullptr;
}

const sf::IntRect KOD::Animation::getFrame(std::size_t index) const
{

	if (index < m_frameList.size() && m_frameList.size()>0)
	{
		return m_frameList[index].getFrameRect();
	}
	return sf::IntRect();
}

const double KOD::Animation::getFrameTime(std::size_t index) const
{
	if (index < m_frameList.size() && m_frameList.size()>0)
	{
		return m_frameList[index].getMaxFrameTime();
	}
	return 0;
}



std::size_t KOD::Animation::getSize() const
{
	return m_frameList.size();
}
