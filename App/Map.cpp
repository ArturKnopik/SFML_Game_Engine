#include "Map.h"

void Map::loadFromFile()
{
	// TODO: stub implementation
	m_width = 50;
	m_height = 50;

	m_map.resize(m_width);
	for (size_t i = 0; i < m_height; i++) {
		m_map[i].resize(m_width);
	}
}
