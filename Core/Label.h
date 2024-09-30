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
	KOD_API virtual void setString(const std::string& text);
	KOD_API virtual const char* getString();
	KOD_API virtual void setFont(sf::Font font);
	KOD_API virtual void setPosition(sf::Vector2f posiition);
	KOD_API virtual void setSize(sf::Vector2f size);
	KOD_API virtual sf::Vector2f getPosition() override;
	KOD_API virtual sf::Vector2f getSize() override;
	KOD_API virtual void setFontSize(unsigned int size);
	KOD_API virtual void setTextColor(sf::Color color);

private:
	sf::Font m_font;
	sf::Text m_text;
	std::string m_cachedAnsiString;
};

} // namespace kod