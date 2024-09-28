#include "Button.h"

#include <SFML/Window/Event.hpp>
#include <iostream>

kod::Button::Button(const std::string& text) : kod::Label(text)
{
	m_rect.setSize(sf::Vector2f(150, 50));
	setColor(sf::Color::White);
	m_rect.setOutlineThickness(3);
	m_rect.setOutlineColor(m_outlineColorOnHover);
	Label::setTextColor(sf::Color::Black);
	updateTextPosition();
}

kod::Button::~Button() {}

void kod::Button::draw(sf::RenderWindow& window)
{
	window.draw(m_rect);
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

	sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
	// override mouse poss in case of click event, required to draw valid outline
	if (event.type == sf::Event::MouseButtonPressed) {
		mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
	}
	sf::Vector2f buttonPos = m_rect.getPosition();
	sf::Vector2f buttonSize = m_rect.getSize();

	if (mousePos.x >= buttonPos.x && mousePos.x <= buttonPos.x + buttonSize.x && mousePos.y >= buttonPos.y &&
	    mousePos.y <= buttonPos.y + buttonSize.y) {
		m_rect.setOutlineColor(m_outlineColorOnHover);
		isHovered = true;
	} else {
		m_rect.setOutlineColor(m_outlineColor);
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
	m_rect.setPosition(posiition);
	updateTextPosition();
}

void kod::Button::setSize(sf::Vector2f size)
{
	Widget::setSize(size);
	m_rect.setSize(size);
	updateTextPosition();
}

void kod::Button::setColor(sf::Color color) { m_rect.setFillColor(color); }

void kod::Button::setOutlineColor(sf::Color color)
{
	m_outlineColor = color;
	m_rect.setOutlineColor(color);
}

void kod::Button::setOutlineColorOnHover(sf::Color color) { m_outlineColorOnHover = color; }

void kod::Button::updateTextPosition()
{
	auto textSize = Label::getSize();
	auto buttonSize = m_rect.getSize();
	auto offsetX = (buttonSize.x - textSize.x) / 2;
	auto offsetY = (buttonSize.y - textSize.y) / 3;
	Label::setPosition({m_rect.getPosition().x + offsetX, m_rect.getPosition().x + offsetY});
}
