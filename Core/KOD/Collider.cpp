#include "IUpdatable.h"
#include "Collider.h"

KOD::Collider::Collider()
{
	m_colliderArray.push_back(ColiderBox());
}


KOD::Collider::Collider(ColiderBox colliderBox)
{
	m_colliderArray.push_back(colliderBox);
}

KOD::Collider::Collider(std::vector<ColiderBox> colliderBoxList)
	:m_colliderArray(colliderBoxList)
{
}

/*
const std::vector<KOD::ColiderBox>& KOD::Collider::getColliders() const
{
	return m_colliderArray;
}
*/