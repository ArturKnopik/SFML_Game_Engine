#include "GameObject.h"

#include "DefinesUtil.h"

kod::GameObject::GameObject() {}

kod::GameObject::GameObject(GameObjectFlags flags) : m_flags(flags) {}

void kod::GameObject::draw(sf::RenderWindow& window)
{
	UNUSED(window);
}

void kod::GameObject::update(const size_t dt)
{
	UNUSED(dt);
}

void kod::GameObject::onCollision() { }

kod::RectBox& kod::GameObject::getBoundingBox() { return m_boundingBox; };

void kod::GameObject::updateBoundingBox(sf::Vector2f pos, sf::Vector2f size)
{
	m_boundingBox.m_position = pos;
	m_boundingBox.m_size = size;
}

kod::RectBox& kod::GameObject::getFlags() { return m_boundingBox; }
