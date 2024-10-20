#pragma once

#include "ComponentManager.h"
#include "Entity.h"
#include "SystemManager.h"

namespace kod {
namespace ecs {

class ECS
{
public:
	KOD_API ECS();
	KOD_API ~ECS() = default;
	KOD_API kod::ecs::SystemManager& getSystemManager();
	KOD_API kod::ecs::ComponentManager& getComponentManager();
	KOD_API void update(const size_t dt);

private:
	kod::ecs::ComponentManager m_componentManager;
	kod::ecs::SystemManager m_systemManager;
};

} // namespace ecs
} // namespace kod