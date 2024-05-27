#pragma once
#include "SFML\Graphics\View.hpp"
#include "SFML\System\Vector2.hpp"
#include "export.h"

#include <vector>

namespace kod {

struct KOD_API RectBox
{
	RectBox() = default;
	RectBox(float x, float y, float width, float height);
	sf::Vector2f m_position = {0, 0};
	sf::Vector2f m_size = {10, 10};
};

class KOD_API ICollider
{
public:
	ICollider();
	ICollider(RectBox colliderBox);
	ICollider(std::vector<RectBox> colliderBoxList);
	const std::vector<kod::RectBox>& getColliders() const;
	std::vector<kod::RectBox>& getColliders();
	const RectBox getSimpleColider();
	const std::vector<RectBox>& getExtendedColider();
	void addColider(RectBox collider);
	virtual void onCollision() = 0;

private:
	RectBox m_coliderBox;
	std::vector<RectBox> m_colliderArray;
	bool m_isCollidable = true;
};
} // namespace kod
