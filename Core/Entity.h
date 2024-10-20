#pragma once
#include "export.h"

#include <array>
#include <bitset>
#include <cstdint>
#include <queue>

namespace kod {
namespace ecs {

using Entity = size_t;
constexpr Entity MAX_ENTITIES = 10000;

using TypeUid = uint16_t;

const TypeUid MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

class EntityManager
{
public:
	KOD_API EntityManager();
	KOD_API ~EntityManager();
	KOD_API Entity newEntity();
	KOD_API void destroyEntity(kod::ecs::Entity entity);
	KOD_API Signature getSignature(kod::ecs::Entity entity);
	KOD_API void setSignature(kod::ecs::Entity entity, kod::ecs::Signature signature);

private:
	std::queue<Entity> m_unusedEntity;
	std::array<Signature, MAX_ENTITIES> m_entitySignature;
	Entity m_livingEntityCount = 0;
};

} // namespace ecs
} // namespace kod
