#pragma once
#include "KOD_export.h"
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\View.hpp"
#include <vector>

namespace KOD
{
	struct ColliderBox
	{
		sf::Vector2f m_position = { 0, 0 };
		sf::Vector2f m_size = { 0, 0 };
	};

	struct BoundingBox
	{
		sf::Vector2f m_position = { 0, 0 };
		sf::Vector2f m_size = { 10 , 10 };
	};

	class KOD_API Collider
	{
		ColliderBox m_coliderBox;
		std::vector<ColliderBox> m_colliderArray;
	public:
		Collider();
		Collider(ColliderBox colliderBox);
		Collider(std::vector<ColliderBox> colliderBoxList);
		const std::vector<KOD::ColliderBox>& getColliders() const;
		const ColliderBox getSimpleColider();
		const std::vector<ColliderBox>& getFullColider();
		void addColider(ColliderBox collider);
		virtual void onCollision() = 0;
	};
}



