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

void kod::Button::handleEvent(sf::Event& event)
{
	if (!(event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed)) {
		return;
	}
	bool isHovered = false;

	sf::Vector2f mousePos(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
	// override mouse poss in case of click event, required to draw valid outline
	if (event.type == sf::Event::MouseButtonPressed) {
		mousePos = sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
	}
	sf::Vector2f buttonPos = m_background.getPosition();
	sf::Vector2f buttonSize = m_background.getSize();

	if (mousePos.x >= buttonPos.x && mousePos.x <= buttonPos.x + buttonSize.x && mousePos.y >= buttonPos.y &&
	    mousePos.y <= buttonPos.y + buttonSize.y) {
		m_background.setOutlineColor(m_outlineColorOnHover);
		isHovered = true;
	} else {
		m_background.setOutlineColor(m_outlineColor);
	}

	if (event.type == sf::Event::MouseButtonPressed) {
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
