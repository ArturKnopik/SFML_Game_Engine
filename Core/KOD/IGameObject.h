#pragma once
#include "KOD_export.h"
#include "IUpdatable.h"
#include "IDrawable.h"
#include "Collider.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <memory>
#include <iostream>



namespace KOD
{
	class IGameObject;
	
	typedef std::shared_ptr<KOD::IGameObject> IGameObject_prt;
	class KOD_API IGameObject
	{
	private:
		static size_t sm_uid;
		size_t m_uid;
	protected:
		sf::Vector2f m_position;
		sf::Sprite m_sprite;
		std::shared_ptr<IUpdatable> m_updatable;
		std::shared_ptr<IDrawable> m_drawable;
		std::shared_ptr<Collider> m_collider;
	public:
		IGameObject();
		IGameObject(std::shared_ptr<IUpdatable> updatable, std::shared_ptr<IDrawable> drawable, std::shared_ptr<Collider> m_solid);
		virtual ~IGameObject() = default;
		const size_t getUid() const;
		void setPosition(const sf::Vector2f position);
		void setPosition(const int positionX, const int positionY);
		const sf::Vector2f getPosition() const;
		std::shared_ptr<IUpdatable> getUpdatable();
		std::shared_ptr<IDrawable> getDrawable();
		const std::shared_ptr<Collider> getCollider() const;
		virtual void onCollision(IGameObject_prt other);
	};
}
