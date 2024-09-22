#pragma once
#include "SFML\Graphics\View.hpp"
#include "SFML\System\Vector2.hpp"
#include "export.h"

#include <vector>

namespace kod {

struct RectBox
{
	KOD_API RectBox() = default;
	KOD_API RectBox(float x, float y, float width, float height);
	sf::Vector2f m_position = {0, 0};
	sf::Vector2f m_size = {10, 10};
};

class ICollider
{
public:
	KOD_API ICollider();
	KOD_API ICollider(RectBox colliderBox);
	KOD_API ICollider(std::vector<RectBox> colliderBoxList);
	KOD_API const std::vector<kod::RectBox>& getColliders() const;
	KOD_API std::vector<kod::RectBox>& getColliders();
	KOD_API const RectBox getSimpleColider();
	KOD_API const std::vector<RectBox>& getExtendedColider();
	KOD_API void addColider(RectBox collider);
	KOD_API virtual void onCollision() = 0;

private:
	RectBox m_coliderBox;
	std::vector<RectBox> m_colliderArray;
	bool m_isCollidable = true;
};
} // namespace kod
