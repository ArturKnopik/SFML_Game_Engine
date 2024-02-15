#include "ICollider.h"

#include "IUpdatable.h"

KOD::ICollider::ICollider() { m_colliderArray.push_back(ColliderBox()); }

KOD::ICollider::ICollider(ColliderBox colliderBox) { m_colliderArray.push_back(colliderBox); }

KOD::ICollider::ICollider(std::vector<ColliderBox> colliderBoxList) : m_colliderArray(colliderBoxList) {}

const std::vector<KOD::ColliderBox>& KOD::ICollider::getColliders() const { return m_colliderArray; }

std::vector<KOD::ColliderBox>& KOD::ICollider::getColliders() { return m_colliderArray; }

const KOD::ColliderBox KOD::ICollider::getSimpleColider() { return m_coliderBox; }

const std::vector<KOD::ColliderBox>& KOD::ICollider::getFullColider() { return m_colliderArray; }

void KOD::ICollider::addColider(KOD::ColliderBox collider)
{
	// TODO: extend change size of m_colliderBox if needed
	m_colliderArray.push_back(collider);
}
