#pragma once

#include "Label.h"

#include <SFML/Graphics.hpp>

namespace kod {

class TextField : public kod::Label
{
public:
	KOD_API TextField();
	KOD_API virtual ~TextField();
	KOD_API virtual void draw(sf::RenderWindow& window) override;
	KOD_API virtual void handleEvent(sf::Event& event) override;
	KOD_API virtual void setPosition(sf::Vector2f position) override;
	KOD_API virtual sf::Vector2f getPosition() override;
	KOD_API virtual void setSize(sf::Vector2f size) override;
	KOD_API virtual sf::Vector2f getSize() override;
	KOD_API virtual const char* getText();
	KOD_API virtual void setOutlineColorOnFocus(sf::Color color);

private:
	void updateTextPosition();

	bool m_hasFocus = false;
	std::string m_inputString;
	sf::RectangleShape m_background;
	sf::RectangleShape m_inputBar;
};

} // namespace kod