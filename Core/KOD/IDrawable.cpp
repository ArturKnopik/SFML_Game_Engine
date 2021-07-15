#include "IDrawable.h"
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>

void KOD::IDrawable::draw(sf::RenderWindow &window)
{
	sf::RectangleShape rect;
	rect.setSize({ 100,100 });
	rect.setFillColor(sf::Color::Green);
	rect.setPosition(100, 199);

	window.draw(rect);
	if (m_animationController.getTexture() == nullptr)
	{
		return;
	}
	if (m_animationController.getAnimation()->getSize() != 0)
	{
		m_sprite.setTexture(*m_animationController.getTexture());
		//m_sprite.setPosition(m_spritePosition.x, m_spritePosition.y);
		m_sprite.setTextureRect(m_animationController.getAnimation()->getFrame(m_animationController.getCurrentFrame()));
		window.draw(m_sprite);
	}
}

void KOD::IDrawable::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}

KOD::AnimationController& KOD::IDrawable::getAnimationController()
{
	return m_animationController;
}

void KOD::IDrawable::updateAnimation(const size_t dt)
{
	m_animationController.update(dt);
}
