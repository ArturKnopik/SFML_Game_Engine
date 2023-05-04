#pragma once
#include "KOD_export.h"
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\View.hpp"
#include <vector>

namespace KOD
{
	struct KOD_API ColliderBox
	{
		sf::Vector2f m_position = { 0, 0 };
		sf::Vector2f m_size = { 0, 0 };
	};

	struct KOD_API BoundingBox
	{
		sf::Vector2f m_position = { 0, 0 };
		sf::Vector2f m_size = { 10 , 10 };
	};

	class KOD_API ICollider
	{
		ColliderBox m_coliderBox;
		std::vector<ColliderBox> m_colliderArray;
		bool m_isCollidable = true;
	public:
		ICollider();
		ICollider(ColliderBox colliderBox);
		ICollider(std::vector<ColliderBox> colliderBoxList);
		const std::vector<KOD::ColliderBox>& getColliders() const;
		std::vector<KOD::ColliderBox>& getColliders();
		const ColliderBox getSimpleColider();
		const std::vector<ColliderBox>& getFullColider();
		void addColider(ColliderBox collider);
		virtual void onCollision() = 0;

	};
}



