#include "IUpdatable.h"
#include "Collider.h"

KOD::Collider::Collider()
{
	m_colliderArray.push_back(ColliderBox());
}


KOD::Collider::Collider(ColliderBox colliderBox)
{
	m_colliderArray.push_back(colliderBox);
}

KOD::Collider::Collider(std::vector<ColliderBox> colliderBoxList)
	:m_colliderArray(colliderBoxList)
{
}

const KOD::ColliderBox KOD::Collider::getSimpleColider()
{
	return m_coliderBox;
}

const std::vector<KOD::ColliderBox>& KOD::Collider::getFullColider()
{
	return m_colliderArray;
}

void KOD::Collider::addColider(KOD::ColliderBox collider)
{
	//TODO: extend change size of m_colliderBox if needed
	m_colliderArray.push_back(collider);
}

