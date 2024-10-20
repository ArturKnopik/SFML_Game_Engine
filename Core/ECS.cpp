#include "ECS.h"

kod::ecs::ECS::ECS() : m_systemManager(SystemManager(m_componentManager)) {}

KOD_API kod::ecs::SystemManager& kod::ecs::ECS::getSystemManager() { return m_systemManager; }

KOD_API kod::ecs::ComponentManager& kod::ecs::ECS::getComponentManager() { return m_componentManager; }

KOD_API void kod::ecs::ECS::update(const size_t dt) { m_systemManager.handleAll(dt); }
