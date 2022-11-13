#pragma once
#include "IUpdatable.h"
#include "IDrawable.h"
#include "IObject.h"
#include "Collider.h"


namespace KOD
{
	struct GameObjectFlags
	{
		bool isCollsionable = false;
	};

	class GameObject
		:public KOD::IObject, public KOD::IDrawable, public KOD::IUpdatable, public KOD::Collider
	{
		BoundingBox m_boundingBox;;
	protected:
		GameObjectFlags m_flags;
	public:
		GameObject() = default;
		GameObject(GameObjectFlags flags) :m_flags(flags) {};
		virtual void draw(sf::RenderWindow& window) override = 0;
		virtual void update(const size_t dt) override = 0;
		virtual void onCollision() override {};
		BoundingBox& getBoundingBox() { return m_boundingBox; };
	};
}

