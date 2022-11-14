#include "GameObject.h"

void KOD::GameObject::updateBoundingBox(sf::Vector2f pos, sf::Vector2f size)
{
	m_boundingBox.m_position = pos;
	m_boundingBox.m_size = size;
}

KOD::BoundingBox& KOD::GameObject::getFlags()
{
	return m_boundingBox;
}
