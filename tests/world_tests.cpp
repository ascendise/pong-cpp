#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include <world/world.hpp>

using ::testing::Eq;
using namespace pong::world;

class FakeComponent : public Component {
private:
    int value;
public:
    void setValue(int value) { this->value = value; };
    int getValue() { return value; };
};

class FakeSystem : public System {
private:
    int value;
public:
    FakeSystem(int value) { this->value = value; };
    void run(std::vector<std::shared_ptr<Entity>> entities) {
        for (auto& entity : entities) {
            auto component = entity.get()->getComponent<FakeComponent>();
            component.get()->setValue(value);
        }
    }
};

TEST(WorldTests, RegisterEntity_ShouldCreateEntityWithUniqueId) {
    //Arrange
    auto component1 = std::make_shared<FakeComponent>(FakeComponent());
    auto components1 = std::vector<std::shared_ptr<Component>>();
    components1.push_back(std::move(component1));
    auto component2 = std::make_shared<FakeComponent>(FakeComponent());
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

TEST(WorldTests, Run_ShouldRunSystemThatModifiesComponents) {
    //Arrange
    auto components = std::vector<std::shared_ptr<Component>>();
    components.push_back(std::make_shared<FakeComponent>(FakeComponent()));
    auto world = pong::world::World();
    //Act
    world.registerSystem(std::make_unique<FakeSystem>(FakeSystem(100)));
    auto entity = world.registerEntity(components);
    world.run();
    //Assert
    auto entity_comp = entity.get()->getComponent<FakeComponent>();
    EXPECT_THAT(entity_comp.get()->getValue(), Eq(100));
}