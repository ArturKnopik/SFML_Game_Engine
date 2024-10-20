#pragma once

#include "ComponentManager.h"
#include "Entity.h"

#include <memory>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>

namespace kod {
namespace ecs {

// duplication in Componets.cpp(only different variable/function maem, TODO: find way to separate it
extern TypeUid g_SystemCounter;

template <class T>
TypeUid getSystemId()
{
	static TypeUid s_componentId = g_SystemCounter++;
	return s_componentId;
}

class System 
{
public:
	KOD_API System() = default;
	KOD_API virtual ~System() = default;
	KOD_API virtual void handle(const size_t dt, ComponentManager& componentManager);
};

class SystemManager
{
public:
	KOD_API SystemManager(ComponentManager& componentManager);

	template <typename T>
	void registerSystem();

	template <typename T>
	T& getSystem();

	KOD_API void handleAll(const size_t dt);

private:
	std::vector<std::shared_ptr<kod::ecs::System>> m_systems;
	ComponentManager& m_componentManager;
};

// #### TEMPLATE IMPLEMENTATION ###

template <typename T>
inline void SystemManager::registerSystem()
{
	static_assert(std::is_base_of<kod::ecs::System, T>::value, "T must be derived from kod::ecs::System!");

	TypeUid typeUid = T::getTypeUid();

	m_systems.insert(m_systems.begin() + typeUid, std::make_shared<T>());
}

template <typename T>
inline T& SystemManager::getSystem()
{
	TypeUid typeUid = T::getTypeUid();

	if (typeUid >= m_systems.size()) {
		throw std::runtime_error("T<" + std::string(std::type_index(typeid(T)).name()) + "> component not registered!");
	}

	if (m_systems[typeUid] == nullptr) {
		throw std::runtime_error("T<" + std::string(std::type_index(typeid(T)).name()) + "> system not initialized!");
	}

	auto system = static_cast<T*>(m_systems[typeUid].get());
	if (!system) {
		throw std::runtime_error("Failed to cast system for type " + std::string(std::type_index(typeid(T)).name()) +
		                         "!");
	}
	return *system;
}

} // namespace ecs
} // namespace kod
