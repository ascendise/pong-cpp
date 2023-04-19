#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include <world/world.hpp>

using ::testing::Eq;
using namespace pong::world;

class DummyComponent : public pong::world::Component { };

TEST(WorldTests, ShouldRegisterEntityWithUniqueId)
{
    //Arrange
    auto component1 = std::make_shared<DummyComponent>(DummyComponent());
    auto components1 = std::vector<std::shared_ptr<Component>>();
    components1.push_back(std::move(component1));
    auto component2 = std::make_shared<DummyComponent>(DummyComponent());
    auto components2 = std::vector<std::shared_ptr<Component>>();
    components2.push_back(std::move(component2));
    auto world = pong::world::World();
    //Act
    auto entity1 = world.registerEntity(components1);
    auto entity2 = world.registerEntity(components2);
    //Assert
    EXPECT_THAT(entity1.get()->getId(), Eq(0));
    EXPECT_THAT(entity2.get()->getId(), Eq(1));
}