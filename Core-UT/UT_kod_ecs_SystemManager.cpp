#include "pch.h" // must be first

#include "../Core/Entity.h"
#include <SystemManager.h>
#include <iostream>

namespace SystemManager {
	/*
	class TestComponent1 : public kod::ecs::Component {
	public:
		int xComponent = 0;
	};

	class TestComponent2 : public kod::ecs::Component {
	public:
		int yComponent = 0;
	};

	class TestSystem1 : public kod::ecs::System {
	public:
		void handle(const size_t dt, kod::ecs::ComponentManager& componentManager) override {
			auto &comps = componentManager.getComponents<TestComponent1>();
			for (size_t i = 0; i < comps.getAllComponents().size(); i++)
			{
				auto& comp1 = comps.getAllComponents()[i];
				comp1.xComponent += static_cast<int>(dt);
			}
			xSystem = 123;
		};
		int xSystem = 0;
	};

	class TestSystem2 : public kod::ecs::System {
	public:
		void handle(const size_t dt, kod::ecs::ComponentManager& componentManager) override {
			auto &comps1 = componentManager.getComponents<TestComponent1>();
			auto &comps2 = componentManager.getComponents<TestComponent2>();
			for (size_t i = 0; i < comps1.getAllComponents().size(); i++)
			{
				auto& comp1 = comps1.getAllComponents()[i];
				comp1.xComponent += static_cast<int>(dt);
				auto& comp2 = comps2.getAllComponents()[i];
				comp2.yComponent += static_cast<int>(i);
			}
			ySystem = 321;
		};
		int ySystem = 0;
	};

	TEST(UT_SystemManager, SystemManager_registerComponent)
	{
		// SETUP
		kod::ecs::ComponentManager cm;
		cm.registerComponent<TestComponent1>();
		cm.registerComponent<TestComponent2>();

		kod::ecs::SystemManager systemManager(cm);

		systemManager.registerSystem<TestSystem1>();
		systemManager.registerSystem<TestSystem2>();

		// THEN
		EXPECT_EQ(systemManager.getSystem<TestSystem1>().getSystemType(), 0);
		EXPECT_EQ(systemManager.getSystem<TestSystem1>().getSystemType(), TestSystem1::getSystemType());
		EXPECT_EQ(systemManager.getSystem<TestSystem2>().getSystemType(), 1);
		EXPECT_EQ(systemManager.getSystem<TestSystem2>().getSystemType(), TestSystem2::getSystemType());
	}
	TEST(UT_SystemManager, SystemManager_handleSystems)
	{
		// SETUP
		kod::ecs::ComponentManager cm;
		cm.registerComponent<TestComponent1>();
		cm.registerComponent<TestComponent2>();

		kod::ecs::SystemManager systemManager(cm);

		systemManager.registerSystem<TestSystem1>();
		systemManager.registerSystem<TestSystem2>();

		systemManager.handleAll(100);

		auto& entity1Data = cm.getComponent<TestComponent1>(static_cast<kod::ecs::Entity>(0));
		auto& entity2Data = cm.getComponent<TestComponent2>(static_cast<kod::ecs::Entity>(0));
		//entity1Data.xComponent;
		//entity2Data.yComponent;

		auto& test1System = systemManager.getSystem<TestSystem1>();
		auto& test2System = systemManager.getSystem<TestSystem2>();

		// THEN
		EXPECT_NE(systemManager.getSystem<TestSystem1>().getSystemType(), systemManager.getSystem<TestSystem2>().getSystemType());
		EXPECT_EQ(systemManager.getSystem<TestSystem1>().getSystemType(), 0);
		EXPECT_EQ(systemManager.getSystem<TestSystem2>().getSystemType(), 1);

		EXPECT_EQ(test1System.xSystem, 123);
		EXPECT_EQ(test2System.ySystem, 321);
		EXPECT_EQ(entity1Data.xComponent, 200);
		EXPECT_EQ(entity2Data.yComponent, 100);
	}
	*/

}