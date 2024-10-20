#pragma once
#include "Entity.h"

#include <stdexcept>
#include <typeindex>

namespace kod {
namespace ecs {

KOD_API extern TypeUid g_componentCounter;

template <class T>
TypeUid getComponentId()
{
	static TypeUid s_componentId = g_componentCounter++;
	return s_componentId;
}

// used for std::array
class IComponents
{
public:
	IComponents() = default;
	virtual ~IComponents() = default;
};

template <typename T>
class ComponentsArray : public IComponents
{
public:
	ComponentsArray();
	virtual ~ComponentsArray() = default;
	T& getData(kod::ecs::Entity entity);
	void setData(kod::ecs::Entity entity, T data);
	TypeUid getComponentType();
	std::array<T, kod::ecs::MAX_ENTITIES>& getAllComponents();

private:
	std::array<T, kod::ecs::MAX_ENTITIES> m_componets;
};

// #### TEMPLATE IMPLEMENTATION ###

template <typename T>
inline ComponentsArray<T>::ComponentsArray()
{
	//to set valid id on registration time
	getComponentId<T>();
}

template <typename T>
inline T& ComponentsArray<T>::getData(kod::ecs::Entity entity)
{
	if (entity >= MAX_ENTITIES) {
		throw std::runtime_error("Can't get data, using Entity that is out of range!");
	}

	return m_componets[entity];
}

template <typename T>
inline void ComponentsArray<T>::setData(kod::ecs::Entity entity, T data)
{
	if (entity >= MAX_ENTITIES) {
		throw std::runtime_error("Can't set data, using Entity that is out of range!");
	}
	m_componets[entity] = data;
}

template <typename T>
inline TypeUid ComponentsArray<T>::getComponentType()
{
	return getComponentId<T>();
}

template <typename T>
inline std::array<T, kod::ecs::MAX_ENTITIES>& ComponentsArray<T>::getAllComponents()
{
	return m_componets;
}

} // namespace ecs
} // namespace kod
