#include "IUpdatable.h"
#include "Collider.h"

KOD::Collider::Collider(sf::Vector2f position, sf::Vector2f size)
{
	m_collisionBoxList.push_back(std::make_pair(position, size));
}

KOD::Collider::Collider(std::vector<std::pair<sf::Vector2f, sf::Vector2f>> colliderBoxList)
	:m_collisionBoxList(colliderBoxList)
{
}

const std::vector<std::pair<sf::Vector2f, sf::Vector2f>>& KOD::Collider::getColliders() const
{
	return m_collisionBoxList;
}

void KOD::Collider::updatePosition(sf::Vector2f position)
{
}
