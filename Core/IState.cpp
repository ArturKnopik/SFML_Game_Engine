
#include "IState.h"

kod::IState::IState(Game& game) : m_game(game) {}

kod::Error kod::IState::addGameObject(std::shared_ptr<kod::GameObject> object)
{
	if (!object) {
		return kod::Error::MEMORY;
	}
	m_gameObjects.insert({object->getUid(), object});
	return kod::Error::OK;
}

kod::Error kod::IState::removeGameObject(std::shared_ptr<kod::GameObject> object)
{
	if (!object) {
		return kod::Error::MEMORY;
	}
	return m_gameObjects.erase(object->getUid()) ? kod::Error::OK : kod::Error::MEMORY;
}

kod::Error kod::IState::removeGameObject(uint64_t uid)
{
	return m_gameObjects.erase(uid) ? kod::Error::OK : kod::Error::MEMORY;
}
