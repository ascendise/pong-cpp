#include <gtest/gtest.h>
#include <physics/physics.hpp>
#include "../test_utility.hpp"

using pong::physics::CollisionEvent;
using pong::physics::CollisionEventProcessor;
using pong::physics::RigidBody;
using pong::physics::BoxCollider;
using pong::math::Vector2D;

TEST(CollisionEventProcessorTests, Process_FrontalCollisionAgainstStaticObject_ShouldChangeVelocityOfEntity) {
    //Arrange
    CollisionEventProcessor sut;
    std::vector<std::shared_ptr<Component>> components;
    auto collider = std::make_shared<BoxCollider>(BoxCollider(Position(0, 0), Vector2D(2, 2)));
    components.push_back(collider);
    auto rigidBody = std::make_shared<RigidBody>(RigidBody());
    rigidBody->getVelocity()->x = 1;
    rigidBody->getVelocity()->y = 0;
    components.push_back(rigidBody);
    auto entity = std::make_shared<Entity>(Entity(1, components));
    //Act
    CollisionEvent event(entity, 90, 1);
    sut.process(std::make_shared<CollisionEvent>(event));
    //Assert
    EXPECT_EQ(rigidBody->getVelocity()->x, -1);
    EXPECT_EQ(test_utility::roundTo(rigidBody->getVelocity()->y, 4), 0);
}

TEST(CollisionEventProcessorTests, Process_FrontalCollisionAgainstStickyObject_ShouldSlowVelocityOfEntity1) {
    //Arrange
    CollisionEventProcessor sut;
    std::vector<std::shared_ptr<Component>> components;
    auto collider = std::make_shared<BoxCollider>(BoxCollider(Position(0, 0), Vector2D(2, 2)));
    components.push_back(collider);
    auto rigidBody = std::make_shared<RigidBody>(RigidBody());
    rigidBody->getVelocity()->x = 1;
    rigidBody->getVelocity()->y = 0;
    components.push_back(rigidBody);
    auto entity = std::make_shared<Entity>(Entity(1, components));
    //Act
    CollisionEvent event(entity, 90, 0.5);
    sut.process(std::make_shared<CollisionEvent>(event));
    //Assert
    EXPECT_EQ(rigidBody->getVelocity()->x, -0.5);
    EXPECT_EQ(test_utility::roundTo(rigidBody->getVelocity()->y, 4), 0);
}

TEST(CollisionEventProcessorTests, Process_FrontalCollisionAgainstStickyObject_ShouldSlowVelocityOfEntity2) {
    //Arrange
    CollisionEventProcessor sut;
    std::vector<std::shared_ptr<Component>> components;
    auto collider = std::make_shared<BoxCollider>(BoxCollider(Position(0, 0), Vector2D(2, 2)));
    components.push_back(collider);
    auto rigidBody = std::make_shared<RigidBody>(RigidBody());
    rigidBody->getVelocity()->x = 10;
    rigidBody->getVelocity()->y = 0;
    components.push_back(rigidBody);
    auto entity = std::make_shared<Entity>(Entity(1, components));
    //Act
    CollisionEvent event(entity, 90, 0.2);
    sut.process(std::make_shared<CollisionEvent>(event));
    //Assert
    EXPECT_EQ(rigidBody->getVelocity()->x, -2);
    EXPECT_EQ(test_utility::roundTo(rigidBody->getVelocity()->y, 4), 0);
}

TEST(CollisionEventProcessorTests, Process_DifferentAngles_ShouldChangeVelocityAngleAccordingly) {
    //Arrange
    CollisionEventProcessor sut;
    std::vector<std::shared_ptr<Component>> components;
    auto collider = std::make_shared<BoxCollider>(BoxCollider(Position(0, 0), Vector2D(2, 2)));
    components.push_back(collider);
    auto rigidBody = std::make_shared<RigidBody>(RigidBody());
    rigidBody->getVelocity()->x = 0;
    rigidBody->getVelocity()->y = 10;
    components.push_back(rigidBody);
    auto entity = std::make_shared<Entity>(Entity(1, components));
    //Act
    CollisionEvent event(entity, 30, 1);
    sut.process(std::make_shared<CollisionEvent>(event));
    //Assert
    EXPECT_EQ(test_utility::roundTo(rigidBody->getVelocity()->x, 6), 8.660254f);
    EXPECT_EQ(test_utility::roundTo(rigidBody->getVelocity()->y, 6), 5);
}