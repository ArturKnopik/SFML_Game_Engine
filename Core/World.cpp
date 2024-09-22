#include "World.h"

#include "DefinesUtil.h"

kod::World::~World() { removaAllObjects(); }

void kod::World::addGameObject(std::shared_ptr<kod::GameObject> obj)
{
	if (!obj) {
		return;
	}
	m_gameObjects.insert({obj->getUid(), obj});
}

void kod::World::removeGameObject(std::shared_ptr<kod::GameObject> obj)
{
	if (!obj) {
		return;
	}
	 m_gameObjects.erase(obj->getUid());
}

void kod::World::removeGameObject(size_t uid)
{
	m_gameObjects.erase(uid);
}

void kod::World::update(const size_t dt) { UNUSED(dt); }

std::unordered_map<size_t, std::shared_ptr<kod::GameObject>>& kod::World::getObjectList() { return m_gameObjects; }

void kod::World::removaAllObjects()
{
	m_gameObjects.clear();
}
