#include "pch.h" // must be first

#include "../Core/Entity.h"

namespace EntityManager {

	TEST(UT_EntityManager, EntityCreationAndDestroy)
	{
		// SETUP
		kod::ecs::EntityManager em;

		// THEN
		for (size_t i = 0; i < kod::ecs::MAX_ENTITIES; i++)
		{
			auto entity = em.newEntity();
			EXPECT_EQ(entity, i);
		}

		// SETUP
		em.destroyEntity(10);
		em.destroyEntity(20);
		em.destroyEntity(25);

		// THEN
		auto entity = em.newEntity();
		EXPECT_EQ(entity, 10);
		entity = em.newEntity();
		EXPECT_EQ(entity, 20);
		entity = em.newEntity();
		EXPECT_EQ(entity, 25);

		EXPECT_THROW(em.newEntity(), std::runtime_error);
		EXPECT_THROW(em.destroyEntity(static_cast<kod::ecs::Entity>(kod::ecs::MAX_ENTITIES + 1)), std::runtime_error);
	}

	TEST(UT_EntityManager, EntitySignature)
	{
		// SETUP
		kod::ecs::EntityManager em;
		auto entityt = em.newEntity();
		auto signature = kod::ecs::Signature();
		signature.set(1, true);
		signature.set(5, true);
		signature.set(10, true);

		// THEN
		em.setSignature(entityt, signature);
		auto testSignature = em.getSignature(entityt);
		EXPECT_EQ(signature, testSignature);
		EXPECT_THROW(em.getSignature(static_cast<kod::ecs::Entity>(kod::ecs::MAX_ENTITIES + 1)), std::runtime_error);
		EXPECT_THROW(em.setSignature(static_cast<kod::ecs::Entity>(kod::ecs::MAX_ENTITIES + 1), kod::ecs::Signature()), std::runtime_error);
	}
}