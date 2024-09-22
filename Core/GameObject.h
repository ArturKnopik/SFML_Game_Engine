#pragma once
#include "ICollider.h"
#include "IDrawable.h"
#include "IObject.h"
#include "IUpdatable.h"

namespace kod {

struct GameObjectFlags
{
	bool isCollisionable = false;
};

class GameObject : public kod::IObject, public kod::IDrawable, public kod::IUpdatable, public kod::ICollider
{
public:
	KOD_API GameObject();
	KOD_API GameObject(GameObjectFlags flags);
	KOD_API virtual void draw(sf::RenderWindow& window) override;
	KOD_API virtual void update(const size_t dt) override;
	KOD_API virtual void onCollision() override;
	KOD_API kod::RectBox& getBoundingBox();
	KOD_API void updateBoundingBox(sf::Vector2f pos, sf::Vector2f size);
	KOD_API kod::RectBox& getFlags();

private:
	kod::RectBox m_boundingBox;

protected:
	GameObjectFlags m_flags;
};
} // namespace kod
