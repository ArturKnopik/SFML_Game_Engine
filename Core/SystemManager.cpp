#include "SystemManager.h"

kod::ecs::TypeUid kod::ecs::g_systemCounter = 0;

kod::ecs::SystemManager::SystemManager(kod::ecs::ComponentManager& componentManager) :
    m_componentManager(componentManager)
{}

void kod::ecs::SystemManager::handleAll(const size_t dt)
{
	for (auto& system : m_systems) {
		if (system) {
			system->handle(dt, m_componentManager);
		}
	}
}

KOD_API void kod::ecs::System::handle(const size_t dt, ComponentManager& componentManager) {}
