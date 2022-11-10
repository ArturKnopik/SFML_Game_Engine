#include "World.h"

KOD::World::World(KOD::BoundingBox qTreeArea)
	:m_qTree(KOD::QuadTree<KOD::GameObject>(qTreeArea.m_position, qTreeArea.m_size, 0))
{
	m_qTree = KOD::QuadTree<KOD::GameObject>(qTreeArea.m_position, qTreeArea.m_size, 0);
}

void KOD::World::addGameObject(std::shared_ptr<KOD::GameObject> obj)
{
	if (!obj)
	{
		return;
	}
	m_gameObjects.insert({ obj->getUid(), obj });
}

void KOD::World::removeGameObject(std::shared_ptr<KOD::GameObject> obj)
{
	if (!obj)
	{
		return;
	}
	m_gameObjects.erase(obj->getUid());
}

void KOD::World::removeGameObject(size_t uid)
{
	m_gameObjects.erase(uid);
}

KOD::uMapObj& KOD::World::getObjectList()
{
	return m_gameObjects;
}
