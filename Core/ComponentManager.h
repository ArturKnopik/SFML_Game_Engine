#pragma once

#include "Components.h"
#include "Entity.h"

#include <memory>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>

namespace kod {
namespace ecs {

class ComponentManager
{
public:
	template <typename T>
	void registerComponent();

	template <typename T>
	kod::ecs::ComponentsArray<T>& getComponents();

	template <typename T>
	T& getComponent(kod::ecs::Entity entity);

	template <typename T>
	TypeUid getComponentType();

	template <typename T>
	void setComponent(kod::ecs::Entity entity, T data);

private:
	std::array<std::shared_ptr<kod::ecs::IComponents>, MAX_COMPONENTS> m_componentsArray{};
};

// #### TEMPLATE IMPLEMENTATION ###

template <typename T>
inline void ComponentManager::registerComponent()
{
	TypeUid typeUid = getComponentId<T>();

	if (typeUid >= MAX_COMPONENTS) {
		throw std::runtime_error("registerComponent: T<" + std::string(std::type_index(typeid(T)).name()) +
		                         "> component already registered!");
	}

	m_componentsArray[typeUid] = std::make_shared<kod::ecs::ComponentsArray<T>>();
	if (m_componentsArray[typeUid] == nullptr) {
		throw std::runtime_error("registerComponent: T<" + std::string(std::type_index(typeid(T)).name()) +
		                         "> fail to create object!");
	}
}

	template <typename T>
	inline ComponentsArray<T>& ComponentManager::getComponents()
	{
	    TypeUid typeUid = getComponentId<T>();

		if (typeUid >= MAX_COMPONENTS) {
			throw std::runtime_error("getComponents: T<" + std::string(std::type_index(typeid(T)).name()) +
			                         "> component type out of range!");
		}

		if (m_componentsArray[typeUid] == nullptr) {
			throw std::runtime_error("getComponents: T<" + std::string(std::type_index(typeid(T)).name()) +
			                         "> component not initialized!");
		}

		auto componentsArray = static_cast<kod::ecs::ComponentsArray<T>*>(m_componentsArray[typeUid].get());
		if (!componentsArray) {
			throw std::runtime_error("getComponents: Failed to cast component array for type " +
			                         std::string(std::type_index(typeid(T)).name()) + "!");
		}
		return *componentsArray;
	}

	template <typename T>
	inline T& ComponentManager::getComponent(kod::ecs::Entity entity)
	{
		return getComponents<T>().getData(entity);
	}

	template <typename T>
    inline TypeUid ComponentManager::getComponentType()
	{
	    TypeUid typeUid = getComponentId<T>();

		if (typeUid >= MAX_COMPONENTS) {
			throw std::runtime_error("getComponent: T<" + std::string(std::type_index(typeid(T)).name()) +
			                         "> component type out of range!");
		}
		return typeUid;
	}

	template <typename T>
	inline void ComponentManager::setComponent(kod::ecs::Entity entity, T data)
	{
	    TypeUid typeUid = getComponentId<T>();

		if (typeUid >= MAX_COMPONENTS) {
			throw std::runtime_error("setComponent: T<" + std::string(std::type_index(typeid(T)).name()) +
			                         "> component type out of range!");
		}

		if (m_componentsArray[typeUid] == nullptr) {
			throw std::runtime_error("setComponent: T<" + std::string(std::type_index(typeid(T)).name()) +
			                         "> component not initialized!");
		}

		getComponents<T>().setData(entity, data);
	}

} // namespace ecs
} // namespace kod
