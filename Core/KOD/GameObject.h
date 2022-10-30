#pragma once
#include "IUpdatable.h"
#include "IDrawable.h"
#include "IObject.h"
struct GameObjectFlags
{
	bool isCollsionable = false;
};

namespace KOD
{
	class GameObject 
		:public KOD::IObject, public KOD::IDrawable, public KOD::IUpdatable
	{
	protected:
		GameObjectFlags m_flags;
	public:
		GameObject() = default;
		GameObject(GameObjectFlags flags) :m_flags(flags) {};
		virtual void draw(sf::RenderWindow& window) override = 0;
		virtual void update(const size_t dt) override = 0;
	};
}

