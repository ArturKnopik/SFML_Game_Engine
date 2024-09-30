#include "IState.h"

#include "Game.h"

kod::IState::IState(Game& game) : m_game(game) {}

void kod::IState::drawGui() { m_gui.draw(m_game.getRenderWindow()); }

void kod::IState::updateGui(const size_t dt) { m_gui.update(dt); }

void kod::IState::input(sf::Event& event) {}

void kod::IState::inputGui(sf::Event& event) { m_gui.handleEvent(event); }

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

void kod::IState::removeGameObject(uint64_t uid) { m_gameObjects.erase(uid); }

void kod::IState::addGuiElement(std::shared_ptr<kod::Widget> uiElement) { m_gui.addElement(uiElement); }

void kod::IState::removeGuiElement(std::shared_ptr<kod::Widget> uiElement) { m_gui.removeElement(uiElement); }
