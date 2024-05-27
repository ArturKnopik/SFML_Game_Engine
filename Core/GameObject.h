#pragma once
#include "ICollider.h"
#include "IDrawable.h"
#include "IObject.h"
#include "IUpdatable.h"

namespace kod {

struct KOD_API GameObjectFlags
{
	bool isCollisionable = false;
};

class KOD_API GameObject : public kod::IObject, public kod::IDrawable, public kod::IUpdatable, public kod::ICollider
{
public:
	GameObject();
	GameObject(GameObjectFlags flags);
	virtual void draw(sf::RenderWindow& window) override;
	virtual void update(const size_t dt) override;
	virtual void onCollision() override;
	kod::RectBox& getBoundingBox();
	void updateBoundingBox(sf::Vector2f pos, sf::Vector2f size);
	kod::RectBox& getFlags();

private:
	kod::RectBox m_boundingBox;

protected:
	GameObjectFlags m_flags;
};
} // namespace KOD
