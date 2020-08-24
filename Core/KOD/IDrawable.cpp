#include "IDrawable.h"

KOD::IDrawable::IDrawable(sf::Vector2f& position)
	:m_spritePosition(position)
{

}

void KOD::IDrawable::draw(std::shared_ptr<sf::RenderWindow> window)
{
	if (m_animationController.getTexture() == nullptr)
	{
		return;
	}
	if (m_animationController.getAnimation()->getSize() != 0)
	{
		m_sprite.setTexture(*m_animationController.getTexture());
		m_sprite.setPosition(m_spritePosition.x, m_spritePosition.y);
		m_sprite.setTextureRect(m_animationController.getAnimation()->getFrame(m_animationController.getCurrentFrame()));
		window->draw(m_sprite);
	}
}

KOD::AnimationController& KOD::IDrawable::getAnimationController()
{
	return m_animationController;
}

void KOD::IDrawable::updateAnimation(const int dt)
{
	m_animationController.update(dt);
}
