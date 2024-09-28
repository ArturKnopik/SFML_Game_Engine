#pragma once
#include "GUI.h"
#include "Label.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <functional>

namespace kod {

using ButtonCb = std::function<void()>;

class Button : public kod::Label
{
public:
	KOD_API Button(const std::string& text);
	KOD_API virtual ~Button();

	KOD_API virtual void draw(sf::RenderWindow& window) override;
	KOD_API virtual void update(size_t dt) override;
	KOD_API virtual void handleEvent(sf::Event& event) override;
	KOD_API virtual void setCallback(ButtonCb callback);
	KOD_API virtual void onClick();
	KOD_API void setPosition(sf::Vector2f posiition);
	KOD_API void setSize(sf::Vector2f size);
	KOD_API void setColor(sf::Color color);
	KOD_API void setOutlineColor(sf::Color color);
	KOD_API void setOutlineColorOnHover(sf::Color color);

private:
	void updateTextPosition();
	sf::RectangleShape m_rect;
	sf::Color m_outlineColor = sf::Color(125, 125, 125, 255);
	sf::Color m_outlineColorOnHover = sf::Color::Black;
	ButtonCb m_callback;

public:
};

} // namespace kod