#include "TextField.h"

kod::TextField::TextField()
{
	setSize(sf::Vector2f(200, 50));
	m_background.setOutlineColor(sf::Color::Red);
	m_inputBar.setFillColor(sf::Color::Black);
	updateTextPosition();
}

kod::TextField::~TextField() {}

void kod::TextField::draw(sf::RenderWindow& window)
{
	window.draw(m_background);
	if (m_hasFocus) {
		window.draw(m_inputBar);
	}
	kod::Label::draw(window);
}

void kod::TextField::handleEvent(sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (m_background.getGlobalBounds().contains(
		        sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) {
			m_hasFocus = true;
			m_background.setOutlineThickness(2);
		} else {
			m_hasFocus = false;
			m_background.setOutlineThickness(0);
		}
	}

	if (m_hasFocus && event.type == sf::Event::TextEntered) {
		if (event.text.unicode < 128) {
			if (event.text.unicode == 10 || event.text.unicode == 13) { // enter linux and windows
				m_hasFocus = false;
				m_background.setOutlineThickness(0);
			} else if (event.text.unicode == '\b' && !m_inputString.empty()) {
				m_inputString.pop_back();
			} else if (event.text.unicode >= 32) {
				m_inputString += static_cast<char>(event.text.unicode);
			}
			kod::Label::setString(m_inputString);
			updateTextPosition();
		}
	}
}

void kod::TextField::setPosition(sf::Vector2f position)
{
	m_background.setPosition(position);
	updateTextPosition();
}

sf::Vector2f kod::TextField::getPosition() { return m_background.getPosition(); }

void kod::TextField::setSize(sf::Vector2f size)
{
	m_background.setSize(size);
	updateTextPosition();
}

sf::Vector2f kod::TextField::getSize() { return m_background.getSize(); }

const char* kod::TextField::getText() { return Label::getString(); }

void kod::TextField::setOutlineColorOnFocus(sf::Color color) { m_background.setOutlineColor(color); }

void kod::TextField::updateTextPosition()
{
	auto textSize = Label::getSize();
	auto bacgroundSize = m_background.getSize();
	auto offsetX = (bacgroundSize.x - textSize.x) / 2;
	auto offsetY = (bacgroundSize.y - textSize.y) / 3;
	Label::setPosition({m_background.getPosition().x + offsetX, m_background.getPosition().y + offsetY});
	m_inputBar.setPosition({Label::getPosition().x + Label::getSize().x + 3, Label::getPosition().y});
	m_inputBar.setSize({2, Label::getSize().y});
}