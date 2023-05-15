#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include <world/world.hpp>
#include "test_doubles/fakes/fake_component.cpp"
#include "test_doubles/fakes/fake_system.cpp"

using ::testing::Eq;
using pong::world::Component;
using pong::world::World;

TEST(WorldTests, RegisterEntity_ShouldCreateEntityWithUniqueId) {
    //Arrange
    auto component1 = std::make_shared<FakeComponent>(FakeComponent());
    auto components1 = std::vector<std::shared_ptr<Component>>();
    components1.push_back(std::move(component1));
    auto component2 = std::make_shared<FakeComponent>(FakeComponent());
    auto components2 = std::vector<std::shared_ptr<Component>>();
    components2.push_back(std::move(component2));
    auto world = World();
    //Act
    auto entity1 = world.registerEntity(components1);
    auto entity2 = world.registerEntity(components2);
    //Assert
    EXPECT_THAT(entity1->getId(), Eq(0));
    EXPECT_THAT(entity2->getId(), Eq(1));
}

TEST(WorldTests, RemoveEntity_ShouldRemoveEntity) {
    //Arrange
    auto world = World();
    auto components = std::vector<std::shared_ptr<Component>>();
    components.push_back(std::make_shared<FakeComponent>(FakeComponent()));
    auto entity = world.registerEntity(components);
    //Act
    world.removeEntity(entity->getId());
    //Assert
    EXPECT_THAT(entity.use_count(), 1);
}

TEST(WorldTests, RemoveEntity_ShouldIgnoreWhenEntityDoesNotExist) {
    //Arrange
    auto world = World();
    //Act
    //Assert
    ASSERT_NO_THROW(world.removeEntity(9999));
}

TEST(WorldTests, Run_ShouldRunSystemThatModifiesComponents) {
    //Arrange
    auto components = std::vector<std::shared_ptr<Component>>();
    components.push_back(std::make_shared<FakeComponent>(FakeComponent()));
    auto world = World();
    //Act
    world.registerSystem(std::make_unique<FakeSystem>(FakeSystem(100)));
    auto entity = world.registerEntity(components);
    world.run();
    //Assert
    auto entity_comp = entity->getComponent<FakeComponent>();
    EXPECT_THAT(entity_comp->getValue(), Eq(100));
}