#pragma once

#include "export.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <unordered_map>

namespace kod {

class Widget
{
public:
	KOD_API Widget();
	KOD_API virtual ~Widget();
	KOD_API virtual void draw(sf::RenderWindow& window);
	KOD_API virtual void update(size_t dt);
	KOD_API virtual void handleEvent(sf::Event& event);
	KOD_API size_t getUid();
	KOD_API const size_t getUid() const;
	// Shoulde be overriden if needed
	KOD_API virtual void setPosition(sf::Vector2f posiition);
	KOD_API virtual sf::Vector2f getPosition();
	KOD_API virtual void setSize(sf::Vector2f size);
	KOD_API virtual sf::Vector2f getSize();

private:
	static size_t sm_uid; // do not touch
	size_t m_uid;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
};

class Gui
{
public:
	KOD_API Gui() = default;
	KOD_API ~Gui() = default;
	KOD_API void draw(sf::RenderWindow& window);
	KOD_API void update(size_t dt);
	KOD_API void handleEvent(sf::Event& event);
	KOD_API void addElement(std::shared_ptr<kod::Widget> widget);
	KOD_API void removeElement(std::shared_ptr<kod::Widget> widget);
	KOD_API void removeElement(size_t uid);
	KOD_API std::shared_ptr<kod::Widget> getElement(size_t id);

private:
	std::unordered_map<size_t, std::shared_ptr<kod::Widget>> m_uiElements;
};

} // namespace kod
