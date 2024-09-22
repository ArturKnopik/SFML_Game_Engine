#pragma once
#include <SFML/Window.hpp>
#include "Tile.h"



class Map
{
public:
	Map();
	void loadFromFile();
	void onUpdate();
	
private:
	uint32_t m_width = 0;
	uint32_t m_height = 0;
	std::vector<std::vector<Tile>> m_map;
	// sf::Vector2i pos;
};
