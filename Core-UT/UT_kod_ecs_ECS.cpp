#include "pch.h" // must be first

#include "../Core/ECS.h"

namespace ECS {

	class TestComponent1 {
	public:
		int xComp = 0;
	};
	
	class TestComponent2 {
	public:
		int yComp = 0;
	};

	class TestSystem1 : public kod::ecs::System {
	public:
		void handle(const size_t dt, kod::ecs::ComponentManager& componentManager) override {
			auto& comps = componentManager.getComponents<TestComponent1>();
			for (size_t i = 0; i < comps.getAllComponents().size(); i++)
			{
				auto& comp = comps.getAllComponents()[i];
				comp.xComp += static_cast<int>(dt + i);
			}
			xSystem = 123;
		};
		int xSystem = 0;
	};

	class TestSystem2 : public kod::ecs::System {
	public:
		void handle(const size_t dt, kod::ecs::ComponentManager& componentManager) override {
			ySystem = 321;
		};
		int ySystem = 0;
	};

	TEST(UT_ECS, Component_getSystemComponent)
	{
		// SETUP
		kod::ecs::g_systemCounter = 0;
		kod::ecs::g_componentCounter = 0;

		kod::ecs::ECS ecs;
		ecs.getComponentManager().registerComponent<TestComponent1>();
		ecs.getComponentManager().registerComponent<TestComponent2>();
		ecs.getSystemManager().registerSystem<TestSystem1>();
		ecs.getSystemManager().registerSystem<TestSystem2>();

		// THEN
		EXPECT_EQ(0, ecs.getComponentManager().getComponentType<TestComponent1>());
		EXPECT_EQ(1, ecs.getComponentManager().getComponentType<TestComponent2>());
		EXPECT_EQ(0, ecs.getSystemManager().getSystem<TestSystem1>().xSystem);
		EXPECT_EQ(0, ecs.getSystemManager().getSystem<TestSystem2>().ySystem);
		EXPECT_EQ(0, ecs.getComponentManager().getComponent<TestComponent1>(static_cast<kod::ecs::Entity>(10)).xComp);
	}
	
	TEST(UT_ECS, Component_update)
	{
		// SETUP
		kod::ecs::g_systemCounter = 0;
		kod::ecs::g_componentCounter = 0;

		kod::ecs::ECS ecs;
		ecs.getComponentManager().registerComponent<TestComponent1>();
		ecs.getComponentManager().registerComponent<TestComponent2>();
		ecs.getSystemManager().registerSystem<TestSystem1>();
		ecs.getSystemManager().registerSystem<TestSystem2>();
		ecs.update(100);

		// THEN
		EXPECT_EQ(123, ecs.getSystemManager().getSystem<TestSystem1>().xSystem);
		EXPECT_EQ(321, ecs.getSystemManager().getSystem<TestSystem2>().ySystem);
		EXPECT_EQ(110, ecs.getComponentManager().getComponent<TestComponent1>(static_cast<kod::ecs::Entity>(10)).xComp);
	}
}