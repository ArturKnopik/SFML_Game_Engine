# Core-UT
UT for `Core` Game Engine made on top of SFML

### Guidelines
* File name - UT_{name_of_tested_files}.cpp. 
	eg: `UT_Particle.cpp`
* Namespaces - name of tested class. 
	eg: `namespace Particle { [...] }`
* `TEST` parameters - UT_{name_of_tested_class} and functionality tested.
	eg: TEST(UT_Particle, Alive)
* Test description - `// Setup` for preparations to test and `// Then` for tests.
* Empty method/functions not require tests.
* If inheritance is required for testing, it must be done.

### Example
```cpp
namespace Particle {

	TEST(UT_Particle, Alive)
	{
		// SETUP
		kod::Particle particle;
		// THEN
		EXPECT_FALSE(particle.isAlive());

		// SETUP
		particle.isAlive(true);
		// THEN
		EXPECT_TRUE(particle.isAlive());
	}

	TEST(UT_Particle, Lifetime)
	{
		// SETUP
		kod::Particle particle;

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
```
