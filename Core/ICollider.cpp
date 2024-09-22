#include "ICollider.h"

#include "IUpdatable.h"

kod::ICollider::ICollider() {}

kod::ICollider::ICollider(RectBox colliderBox) { m_colliderArray.push_back(colliderBox); }

kod::ICollider::ICollider(std::vector<RectBox> colliderBoxList) : m_colliderArray(colliderBoxList) {}

const std::vector<kod::RectBox>& kod::ICollider::getColliders() const { return m_colliderArray; }

std::vector<kod::RectBox>& kod::ICollider::getColliders() { return m_colliderArray; }

const kod::RectBox kod::ICollider::getSimpleColider() { return m_coliderBox; }

const std::vector<kod::RectBox>& kod::ICollider::getExtendedColider() { return m_colliderArray; }

void kod::ICollider::addColider(kod::RectBox collider)
{
	// TODO: extend change size of m_colliderBox if needed
	m_colliderArray.push_back(collider);
}

kod::RectBox::RectBox(float x, float y, float width, float height)
{
	m_position.x = x;
	m_position.y = y;
	m_size.x = width;
	m_size.y = height;
}
