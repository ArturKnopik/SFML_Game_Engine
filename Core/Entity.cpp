#include "Entity.h"

#include <cassert>
#include <stdexcept>

kod::ecs::EntityManager::EntityManager()
{
	for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
		m_unusedEntity.push(entity);
	}
}

kod::ecs::EntityManager::~EntityManager() {}

kod::ecs::Entity kod::ecs::EntityManager::newEntity()
{
	if (m_livingEntityCount >= MAX_ENTITIES) {
		throw std::runtime_error("Can't create new Entity, limit reached!");
	}

	Entity id = m_unusedEntity.front();
	m_unusedEntity.pop();
	m_livingEntityCount++;
	return id;
}

void kod::ecs::EntityManager::destroyEntity(kod::ecs::Entity entity)
{
	if (entity >= MAX_ENTITIES) {
		throw std::runtime_error("Can't destory Entity that is out of range!");
	}

	m_unusedEntity.push(entity);
	m_livingEntityCount--;
	m_entitySignature[entity].reset();
}

kod::ecs::Signature kod::ecs::EntityManager::getSignature(kod::ecs::Entity entity)
{
	if (m_livingEntityCount >= MAX_ENTITIES || entity >= MAX_ENTITIES) {
		throw std::runtime_error("Can't set signature for Entity that is out of range!");
	}
	return m_entitySignature[entity];
}


void kod::ecs::EntityManager::setSignature(kod::ecs::Entity entity, kod::ecs::Signature signature)
{
	if (m_livingEntityCount >= MAX_ENTITIES || entity >= MAX_ENTITIES) {
		throw std::runtime_error("Can't set signature for Entity that is out of range!");
	}
	m_entitySignature[entity] = signature;
}
