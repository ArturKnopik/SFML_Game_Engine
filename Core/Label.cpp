#include "Label.h"

kod::Label::Label()
{
	m_text.setCharacterSize(10);
	m_text.setFillColor(sf::Color::Black);
}

kod::Label::Label(const std::string& text)
{
	m_text.setString(text);
	m_text.setCharacterSize(10);
}

kod::Label::~Label() {}

void kod::Label::draw(sf::RenderWindow& window) { window.draw(m_text); }

void kod::Label::setString(const std::string& text) { m_text.setString(text); }

void kod::Label::setFont(sf::Font font)
{
	m_font = font;
	m_text.setFont(m_font);
}

void kod::Label::setPosition(sf::Vector2f posiition)
{
	kod::Widget::setPosition(posiition);
	m_text.setPosition(posiition);
}

void kod::Label::setSize(sf::Vector2f size)
{
	kod::Widget::setSize(size);
	m_text.setPosition(size);
}

sf::Vector2f kod::Label::getPosition() { return m_text.getGlobalBounds().getPosition(); }

sf::Vector2f kod::Label::getSize() { return m_text.getGlobalBounds().getSize(); }

void kod::Label::setFontSize(size_t size) { m_text.setCharacterSize(size); }

void kod::Label::setTextColor(sf::Color color) { m_text.setFillColor(color); }
