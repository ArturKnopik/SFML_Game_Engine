#include "pch.h" // must be first

#include "../Core/Entity.h"
#include <ComponentManager.h>
#include <iostream>

namespace ComponentManager {

	class TestComponent {
	public:
		int x = 0;
	};

	TEST(UT_ComponentManager, ComponentManager_registerComponent)
	{
		// SETUP
		kod::ecs::g_componentCounter = 0;
		auto entity = kod::ecs::EntityManager().newEntity();
		kod::ecs::ComponentManager components;
		components.registerComponent<TestComponent>();
		auto component = TestComponent();
		component.x = 1000;
		components.setComponent<TestComponent>(entity, component);
		auto testComponent = components.getComponent<TestComponent>(entity);

		// THEN
		EXPECT_EQ(component.x, testComponent.x);
	}

	TEST(UT_ComponentManager, ComponentManager_getComponents)
	{
		// SETUP
		kod::ecs::g_componentCounter = 0;
		auto entity = kod::ecs::EntityManager().newEntity();
		kod::ecs::ComponentManager components;
		components.registerComponent<TestComponent>();
		auto component = TestComponent();
		component.x = 1000;
		components.setComponent<TestComponent>(entity, component);

		auto testComponents = components.getComponents<TestComponent>();
		// THEN
		// Component array should return the same component type like template parameter
		EXPECT_EQ(0, testComponents.getComponentType());
		EXPECT_EQ(component.x, testComponents.getData(entity).x);
	}

}