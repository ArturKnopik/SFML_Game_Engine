#pragma once
#include "KOD_export.h"
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\View.hpp"
#include <vector>

namespace KOD
{
	class KOD_API Collider
	{						
	/*
	*											box size
	*												||
	*							position offset		||
	*								||				||
	*								\/				\/
	*/
		std::vector<std::pair<sf::Vector2f, sf::Vector2f>> m_collisionBoxList;
	public:
		Collider() = delete;
		Collider(sf::Vector2f position, sf::Vector2f size);
		Collider(std::vector<std::pair<sf::Vector2f, sf::Vector2f>> colliderBoxList);
		const std::vector<std::pair<sf::Vector2f, sf::Vector2f>>& getColliders() const;
		void updatePosition(sf::Vector2f position);
	};
}



