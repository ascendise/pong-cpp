#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include <world/world.hpp>

using ::testing::Eq;

class DummyComponent : public pong::world::Component { };

TEST(WorldTests, ShouldRegisterEntityWithUniqueId)
{
    //Arrange
    std::unique_ptr<pong::world::Component> components1[] = { std::make_unique<pong::world::Component>(DummyComponent()) };
    std::unique_ptr<pong::world::Component> components2[] = { std::make_unique<pong::world::Component>(DummyComponent()) };
    auto world = pong::world::World();
    //Act
    auto entity1 = world.registerEntity(components1);
    auto entity2 = world.registerEntity(components2);
    //Assert
    EXPECT_THAT(entity1.getId(), Eq(0));
    EXPECT_THAT(entity2.getId(), Eq(1));
}