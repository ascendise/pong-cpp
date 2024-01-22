#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include <world.hpp>
#include <events.hpp>
#include <world_doubles.hpp>
#include <event_doubles.hpp>

namespace pong::world {


	TEST(WorldTests, RegisterEntity_ShouldCreateEntityWithUniqueId) {
	    //Arrange
	    auto component1 = std::make_unique<testing::FakeComponent>(testing::FakeComponent());
	    auto components1 = std::vector<std::unique_ptr<Component>>();
	    components1.push_back(std::move(component1));
	    auto component2 = std::make_unique<testing::FakeComponent>(testing::FakeComponent());
	    auto components2 = std::vector<std::unique_ptr<Component>>();
	    components2.push_back(std::move(component2));
	    auto world = World(std::make_unique<testing::StubEventQueue>());
	    //Act
	    world.registerEntity(std::move(components1));
	    world.registerEntity(std::move(components2));
	    //Assert
	    auto entity1 = world.findEntity(0);
	    auto entity2 = world.findEntity(1);
	    EXPECT_TRUE(entity1.has_value());
	    EXPECT_TRUE(entity2.has_value());
	}
	
	TEST(WorldTests, RemoveEntity_ShouldRemoveEntity) {
	    //Arrange
	    auto world = World(std::make_unique<testing::StubEventQueue>());
	    auto components = std::vector<std::unique_ptr<Component>>();
	    components.push_back(std::make_unique<testing::FakeComponent>(testing::FakeComponent()));
	    world.registerEntity(std::move(components));
	    //Act
	    world.removeEntity(0);
	    //Assert
	    auto entity = world.findEntity(0);
	    EXPECT_FALSE(entity.has_value());
	}
	
	TEST(WorldTests, RemoveEntity_ShouldIgnoreWhenEntityDoesNotExist) {
	    //Arrange
	    auto world = World(std::make_unique<testing::StubEventQueue>());
	    //Act
	    //Assert
	    ASSERT_NO_THROW(world.removeEntity(9999));
	}
	
	TEST(WorldTests, Run_ShouldRunSystemThatModifiesComponents) {
	    //Arrange
	    auto components = std::vector<std::unique_ptr<Component>>();
	    components.push_back(std::make_unique<testing::FakeComponent>());
	    auto world = World(std::make_unique<testing::StubEventQueue>());
	    //Act
	    world.registerSystem(std::make_unique<testing::FakeSystem>(100));
	    world.registerEntity(std::move(components));
	    world.run();
	    //Assert
	    auto& entity = world.findEntity(0).value().get(); //NOLINT bugprone-unchecked-optional-access
	    auto modified_comp = entity.getComponent<testing::FakeComponent>().value().get(); //NOLINT bugprone-unchecked-optional-access
	    EXPECT_THAT(modified_comp.getValue(), 100);
	}
	
	
	TEST(WorldTests, Run_ShouldRunEventQueue) {
	    //Arrange
	    auto eventQueue = std::make_unique<events::EventQueue>();
	    eventQueue->registerProcessor(std::make_unique<events::testing::FakeEventProcessor>());
	    World world(std::move(eventQueue));
	    int processCount = 0;
	    //Act
	    world.getEventQueue().enqueue(std::make_shared<events::testing::FakeEvent>(&processCount));
	    world.run();
	    //Assert
	    ASSERT_EQ(processCount, 1);
	}
}
