#include <gtest/gtest.h>
#include <physics.hpp>
#include <test_utility.hpp>

using pong::physics::CollisionEvent;
using pong::physics::CollisionEventProcessor;
using pong::physics::RigidBody;
using pong::physics::BoxCollider;
using pong::math::Vector2D;

TEST(CollisionEventProcessorTests, Process_FrontalCollisionAgainstStaticObject_ShouldChangeVelocityOfEntity) {
    //Arrange
    CollisionEventProcessor sut;
    std::vector<std::unique_ptr<Component>> components;
    auto collider = std::make_unique<BoxCollider>(Position(0, 0), Vector2D(2, 2));
    components.push_back(std::move(collider));
    auto rigidBody = std::make_unique<RigidBody>();
    rigidBody->getVelocity().x = 1;
    rigidBody->getVelocity().y = 0;
    components.push_back(std::move(rigidBody));
    Entity entity(1, std::move(components));
    //Act
    CollisionEvent event(entity, 90, 1);
    sut.process(event);
    //Assert
    auto& newRigidbody = entity.getComponent<RigidBody>().value().get();
    EXPECT_EQ(newRigidbody.getVelocity().x, -1);
    EXPECT_EQ(test_utility::roundTo(newRigidbody.getVelocity().y, 4), 0);
}

TEST(CollisionEventProcessorTests, Process_FrontalCollisionAgainstStickyObject_ShouldSlowVelocityOfEntity1) {
    //Arrange
    CollisionEventProcessor sut;
    std::vector<std::unique_ptr<Component>> components;
    auto collider = std::make_unique<BoxCollider>(Position(0, 0), Vector2D(2, 2));
    components.push_back(std::move(collider));
    auto rigidBody = std::make_unique<RigidBody>();
    rigidBody->getVelocity().x = 1;
    rigidBody->getVelocity().y = 0;
    components.push_back(std::move(rigidBody));
    Entity entity(1, std::move(components));
    //Act
    CollisionEvent event(entity, 90, 0.5);
    sut.process(event);
    //Assert
    auto& newRigidbody = entity.getComponent<RigidBody>().value().get();
    EXPECT_EQ(newRigidbody.getVelocity().x, -0.5);
    EXPECT_EQ(test_utility::roundTo(newRigidbody.getVelocity().y, 4), 0);
}

TEST(CollisionEventProcessorTests, Process_FrontalCollisionAgainstStickyObject_ShouldSlowVelocityOfEntity2) {
    //Arrange
    CollisionEventProcessor sut;
    std::vector<std::unique_ptr<Component>> components;
    auto collider = std::make_unique<BoxCollider>(Position(0, 0), Vector2D(2, 2));
    components.push_back(std::move(collider));
    auto rigidBody = std::make_unique<RigidBody>();
    rigidBody->getVelocity().x = 10;
    rigidBody->getVelocity().y = 0;
    components.push_back(std::move(rigidBody));
    Entity entity(1, std::move(components));
    //Act
    CollisionEvent event(entity, 90, 0.2);
    sut.process(event);
    //Assert
    auto& newRigidBody = entity.getComponent<RigidBody>().value().get();
    EXPECT_EQ(newRigidBody.getVelocity().x, -2);
    EXPECT_EQ(test_utility::roundTo(newRigidBody.getVelocity().y, 4), 0);
}

TEST(CollisionEventProcessorTests, Process_DifferentAngles_ShouldChangeVelocityAngleAccordingly) {
    //Arrange
    CollisionEventProcessor sut;
    std::vector<std::unique_ptr<Component>> components;
    auto collider = std::make_unique<BoxCollider>(Position(0, 0), Vector2D(2, 2));
    components.push_back(std::move(collider));
    auto rigidBody = std::make_unique<RigidBody>();
    rigidBody->getVelocity().x = 0;
    rigidBody->getVelocity().y = 10;
    components.push_back(std::move(rigidBody));
    Entity entity(1, std::move(components));
    //Act
    CollisionEvent event(entity, 30, 1);
    sut.process(event);
    auto newRigidBody = entity.getComponent<RigidBody>().value().get();
    //Assert
    EXPECT_EQ(test_utility::roundTo(newRigidBody.getVelocity().x, 6), 8.660254f);
    EXPECT_EQ(test_utility::roundTo(newRigidBody.getVelocity().y, 6), 5);
}