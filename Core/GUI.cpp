#include "Gui.h"

size_t kod::Widget::sm_uid = 0;

kod::Widget::Widget() : m_uid(sm_uid++) {}

kod::Widget::~Widget() {}

void kod::Widget::draw(sf::RenderWindow& window) {}

void kod::Widget::update(size_t dt) {}

void kod::Widget::handleEvent(sf::Event& event) {}

const size_t kod::Widget::getUid() const { return m_uid; }

void kod::Widget::setPosition(sf::Vector2f posiition) { }

sf::Vector2f kod::Widget::getPosition() { return sf::Vector2f(); }

void kod::Widget::setSize(sf::Vector2f size) { }

sf::Vector2f kod::Widget::getSize() { return sf::Vector2f(); }

size_t kod::Widget::getUid() { return m_uid; }

void kod::Gui::draw(sf::RenderWindow& window)
{
	for (auto& uiElement : m_uiElements) {
		// Do stuff
		uiElement.second->draw(window);
	}
}
void kod::Gui::update(size_t dt)
{
	for (auto& uiElement : m_uiElements) {
		uiElement.second->update(dt);
	}
}

void kod::Gui::handleEvent(sf::Event& event)
{
	for (auto& uiElement : m_uiElements) {
		uiElement.second->handleEvent(event);
	}
}

void kod::Gui::addElement(std::shared_ptr<Widget> widget) { m_uiElements.emplace(widget->getUid(), widget); }

void kod::Gui::removeElement(std::shared_ptr<kod::Widget> widget) { m_uiElements.erase(widget->getUid()); }

void kod::Gui::removeElement(size_t uid) { m_uiElements.erase(uid); }
