#include "pch.h" // must be first

#include "Particle.h"

namespace Particle {

	TEST(UT_Particle, Alive)
	{
		// PREPARE
		kod::Particle particle;
		// SETUP
		// THEN
		EXPECT_FALSE(particle.isAlive());

		// SETUP
		particle.isAlive(true);
		// THEN
		EXPECT_TRUE(particle.isAlive());
	}

	TEST(UT_Particle, Lifetime)
	{
		// PREPARE
		kod::Particle particle;

		// SETUP
		// THEN
		EXPECT_EQ(0, particle.getCurrentLifeTime());
		EXPECT_EQ(kod::time::TIME_1S, particle.getMaxLifeTime());

		// SETUP
		particle.setMaxLifeTime(1000);
		// THEN
		EXPECT_EQ(1000, particle.getMaxLifeTime());

		// SETUP
		particle.updateLifeTime(123);
		// THEN
		EXPECT_EQ(123, particle.getCurrentLifeTime());

		// SETUP
		particle.isAlive(true);
		particle.updateLifeTime(1000);
		// THEN
		EXPECT_EQ(1123, particle.getCurrentLifeTime());
		EXPECT_FALSE(particle.isAlive());

		// SETUP
		particle.reset();
		// THEN
		EXPECT_EQ(0, particle.getCurrentLifeTime());
		EXPECT_EQ(1000, particle.getMaxLifeTime());
		EXPECT_TRUE(particle.isAlive());
	}
}