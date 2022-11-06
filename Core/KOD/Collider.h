#pragma once
#include "KOD_export.h"
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\View.hpp"
#include <vector>

namespace KOD
{
	struct ColiderBox
	{
		sf::Vector2f pos = { 0, 0 };
		sf::Vector2f size = { 0, 0 };
	};

	class KOD_API Collider
	{		
		ColiderBox m_coliderBox;
		std::vector<ColiderBox> m_colliderArray;
	public:
		Collider();
		Collider(ColiderBox colliderBox);
		Collider(std::vector<ColiderBox> colliderBoxList);
		const std::vector<KOD::ColiderBox>& getColliders() const;
	};
}



