
#include "IState.h"

kod::IState::IState(Game& game) : m_game(game) {}

void kod::IState::input(sf::Event& event) {}

void kod::IState::input() {}

void kod::IState::addGameObject(std::shared_ptr<kod::GameObject> object)
{
	if (!object) {
		return;
	}
	m_gameObjects.insert({object->getUid(), object});
}

void kod::IState::removeGameObject(std::shared_ptr<kod::GameObject> object)
{
	if (!object) {
		return;
	}
	m_gameObjects.erase(object->getUid());
}

void kod::IState::removeGameObject(uint64_t uid)
{
	m_gameObjects.erase(uid);
}
