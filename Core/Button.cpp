#include "Button.h"

#include <SFML/Window/Event.hpp>
#include <iostream>

kod::Button::Button(const std::string& text) : kod::Label(text)
{
	m_background.setSize(sf::Vector2f(150, 50));
	setColor(sf::Color::White);
	m_background.setOutlineThickness(3);
	m_background.setOutlineColor(m_outlineColorOnHover);
	Label::setTextColor(sf::Color::Black);
	updateTextPosition();
}

kod::Button::~Button() {}

void kod::Button::draw(sf::RenderWindow& window)
{
	window.draw(m_background);
	Label::draw(window);
	kod::Label::draw(window);
}

void kod::Button::update(size_t dt) { kod::Label::update(dt); }

void kod::Button::handleEvent(const std::optional<sf::Event>& event)
{
	if (!event.has_value()) {
		return;
	}

	bool isHovered = false;
	sf::Vector2f mousePos;

	if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
		mousePos = {float(mouseMoved->position.x), float(mouseMoved->position.y)};
	} else if (auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
		mousePos = {float(mouseButtonPressed->position.x), float(mouseButtonPressed->position.y)};
	} else {
		return;
	}

	const auto buttonPos = m_background.getPosition();
	const auto buttonSize = m_background.getSize();

	if (mousePos.x >= buttonPos.x && mousePos.x <= buttonPos.x + buttonSize.x && mousePos.y >= buttonPos.y &&
	    mousePos.y <= buttonPos.y + buttonSize.y) {
		m_background.setOutlineColor(m_outlineColorOnHover);
		isHovered = true;
	} else {
		m_background.setOutlineColor(m_outlineColor);
	}

	if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
		if (isHovered) {
			onClick();
		}
	}
}

void kod::Button::setCallback(ButtonCb callback) { m_callback = callback; }

void kod::Button::onClick()
{
	if (m_callback) {
		m_callback();
	}
}

void kod::Button::setPosition(sf::Vector2f posiition)
{
	Widget::setPosition(posiition);
	m_background.setPosition(posiition);
	updateTextPosition();
}

void kod::Button::setSize(sf::Vector2f size)
{
	Widget::setSize(size);
	m_background.setSize(size);
	updateTextPosition();
}

void kod::Button::setColor(sf::Color color) { m_background.setFillColor(color); }

void kod::Button::setOutlineColor(sf::Color color)
{
	m_outlineColor = color;
	m_background.setOutlineColor(color);
}

void kod::Button::setOutlineColorOnHover(sf::Color color) { m_outlineColorOnHover = color; }

void kod::Button::setString(const std::string& text)
{
	Label::setString(text);
	updateTextPosition();
}

void kod::Button::updateTextPosition()
{
	sf::Vector2f textSize = Label::getSize();
	sf::Vector2f buttonSize = m_background.getSize();
	float offsetX = (buttonSize.x - textSize.x) / 2;
	float offsetY = (buttonSize.y - textSize.y) / 3;
	Label::setPosition({m_background.getPosition().x + offsetX, m_background.getPosition().y + offsetY});
}
