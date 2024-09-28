#pragma once
#include "Gui.h"
#include "export.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

namespace kod {

class Label : public kod::Widget
{
public:
	KOD_API Label();
	KOD_API Label(const std::string& text);
	KOD_API virtual ~Label();
	KOD_API virtual void draw(sf::RenderWindow& window) override;
	KOD_API void setString(const std::string& text);
	KOD_API void setFont(sf::Font font);
	KOD_API void setPosition(sf::Vector2f posiition);
	KOD_API void setSize(sf::Vector2f size);
	KOD_API sf::Vector2f getPosition() override;
	KOD_API sf::Vector2f getSize() override;
	KOD_API void setFontSize(size_t size);
	KOD_API void setTextColor(sf::Color color);

private:
	sf::Font m_font;
	sf::Text m_text;
};

} // namespace kod