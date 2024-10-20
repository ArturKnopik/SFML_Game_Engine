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
		em.destroyEntity(1);

		// THEN
		auto entity = em.newEntity();
		EXPECT_EQ(entity, 10);
		entity = em.newEntity();
		EXPECT_EQ(entity, 20);
		entity = em.newEntity();
		EXPECT_EQ(entity, 25);
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
	}
}