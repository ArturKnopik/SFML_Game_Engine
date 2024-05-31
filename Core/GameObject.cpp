#include "GameObject.h"

#include "DefinesUtil.h"

kod::GameObject::GameObject() {}

kod::GameObject::GameObject(GameObjectFlags flags) : m_flags(flags) {}

kod::Error kod::GameObject::draw(sf::RenderWindow& window)
{
	UNUSED(window);
	return Error::OK;
}

kod::Error kod::GameObject::update(const size_t dt)
{
	UNUSED(dt);
	return Error::OK;
}

kod::Error kod::GameObject::onCollision() { return Error::OK; }

kod::RectBox& kod::GameObject::getBoundingBox() { return m_boundingBox; };

kod::Error kod::GameObject::updateBoundingBox(sf::Vector2f pos, sf::Vector2f size)
{
	m_boundingBox.m_position = pos;
	m_boundingBox.m_size = size;
	return Error::OK;
}

kod::RectBox& kod::GameObject::getFlags() { return m_boundingBox; }
