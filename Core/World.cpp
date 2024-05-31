#include "World.h"

#include "DefinesUtil.h"

kod::World::~World() { removaAllObjects(); }

kod::Error kod::World::addGameObject(std::shared_ptr<kod::GameObject> obj)
{
	if (!obj) {
		return Error::INVALID_INPUT;
	}
	m_gameObjects.insert({obj->getUid(), obj});
	return Error::OK;
}

kod::Error kod::World::removeGameObject(std::shared_ptr<kod::GameObject> obj)
{
	if (!obj) {
		return Error::INVALID_INPUT;
	}
	return m_gameObjects.erase(obj->getUid()) ? Error::OK : Error::INVALID_CALL;
}

kod::Error kod::World::removeGameObject(size_t uid)
{
	return m_gameObjects.erase(uid) ? Error::OK : Error::INVALID_CALL;
}

kod::Error kod::World::update(const size_t dt)
{
	UNUSED(dt);
	return Error::OK;
}

std::unordered_map<size_t, std::shared_ptr<kod::GameObject>>& kod::World::getObjectList() { return m_gameObjects; }

kod::Error kod::World::removaAllObjects()
{
	m_gameObjects.clear();
	return Error::OK;
}
