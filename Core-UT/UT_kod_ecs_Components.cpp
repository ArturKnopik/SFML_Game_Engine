#include "pch.h" // must be first

#include "../Core/Entity.h"
#include "../Core/Components.h"

namespace Component {

	class TestComponent {
	public:
		int x = 0;
	};

	class TestAnotherComponent {
	public:
		int y = 0;
	};

	TEST(UT_Component, Component_registerComponent)
	{
		// SETUP
		kod::ecs::ComponentsArray<TestComponent> components;
		kod::ecs::ComponentsArray<TestAnotherComponent> anotherComponent;

		// THEN
		EXPECT_NE(components.getComponentType(), anotherComponent.getComponentType());
		EXPECT_EQ(0, components.getComponentType());
		EXPECT_EQ(1, anotherComponent.getComponentType());
	}

	TEST(UT_Component, Component_getSetComponentData)
	{
		// SETUP
		kod::ecs::ComponentsArray<TestComponent> components;
		kod::ecs::EntityManager em;
		kod::ecs::Entity entity = em.newEntity();
		auto testComp = TestComponent();
		testComp.x = 123;
		components.setData(entity, testComp);

		// THEN
		EXPECT_EQ(123, components.getData(entity).x);

		// SETUP
		kod::ecs::ComponentsArray<TestAnotherComponent> anotherComponent;
		auto testAnotherComp = TestAnotherComponent();
		testAnotherComp.y = 555;
		anotherComponent.setData(entity, testAnotherComp);
		// THEN
		EXPECT_EQ(555, anotherComponent.getData(entity).y);
	}

	TEST(UT_ComponentManager, ComponentManager_getAllComponentData)
	{
		// SETUP
		kod::ecs::ComponentsArray<TestComponent> components;
		kod::ecs::EntityManager em;
		kod::ecs::Entity entity = em.newEntity();
		auto testComp = TestComponent();
		testComp.x = 123;
		components.setData(entity, testComp);

		// THEN
		EXPECT_EQ(123, components.getAllComponents()[entity].x);
		EXPECT_EQ(0, components.getAllComponents()[em.newEntity()].x);
	}
}