#include <math.hpp>
#include <physics.hpp>
#include <test_utility.hpp>

#include <gtest/gtest.h>

namespace pong::physics {

TEST(CollisionEventProcessorTests, Process_FrontalCollisionAgainstStaticObject_ShouldChangeVelocityOfEntity) {
  // Arrange
  CollisionEventProcessor sut;
  std::vector<std::unique_ptr<world::Component>> components;
  auto collider = std::make_unique<BoxCollider>(world::Position(0, 0), math::Vector2D(2, 2));
  components.push_back(std::move(collider));
  auto rigidBody = std::make_unique<RigidBody>(math::Vector2D(1, 0), 1);
  components.push_back(std::move(rigidBody));
  world::Entity entity(1, std::move(components));
  // Act
  CollisionEvent const event(entity, 90, 1);
  sut.process(event);
  // Assert
  auto &newRigidbody = entity.getComponent<RigidBody>().value().get(); // NOLINT bugprone-unchecked-optional-access
  EXPECT_EQ(newRigidbody.getVelocity().x, -1);
  EXPECT_EQ(test_utility::roundTo(newRigidbody.getVelocity().y, 4), 0);
}

TEST(CollisionEventProcessorTests, Process_FrontalCollisionAgainstStickyObject_ShouldSlowVelocityOfEntity1) {
  // Arrange
  CollisionEventProcessor sut;
  std::vector<std::unique_ptr<world::Component>> components;
  auto collider = std::make_unique<BoxCollider>(world::Position(0, 0), math::Vector2D(2, 2));
  components.push_back(std::move(collider));
  auto rigidBody = std::make_unique<RigidBody>(math::Vector2D(1, 0), 1);
  components.push_back(std::move(rigidBody));
  world::Entity entity(1, std::move(components));
  // Act
  CollisionEvent const event(entity, 90, 0.5);
  sut.process(event);
  // Assert
  auto &newRigidbody = entity.getComponent<RigidBody>().value().get(); // NOLINT bugprone-unchecked-optional-access
  EXPECT_EQ(newRigidbody.getVelocity().x, -0.5);
  EXPECT_EQ(test_utility::roundTo(newRigidbody.getVelocity().y, 4), 0);
}

TEST(CollisionEventProcessorTests, Process_FrontalCollisionAgainstStickyObject_ShouldSlowVelocityOfEntity2) {
  // Arrange
  CollisionEventProcessor sut;
  std::vector<std::unique_ptr<world::Component>> components;
  auto collider = std::make_unique<BoxCollider>(world::Position(0, 0), math::Vector2D(2, 2));
  components.push_back(std::move(collider));
  auto rigidBody = std::make_unique<RigidBody>(math::Vector2D(10, 0), 1);
  components.push_back(std::move(rigidBody));
  world::Entity entity(1, std::move(components));
  // Act
  CollisionEvent const event(entity, 90, 0.2);
  sut.process(event);
  // Assert
  auto &newRigidBody = entity.getComponent<RigidBody>().value().get(); // NOLINT bugprone-unchecked-optional-access
  EXPECT_EQ(newRigidBody.getVelocity().x, -2);
  EXPECT_EQ(test_utility::roundTo(newRigidBody.getVelocity().y, 4), 0);
}

TEST(CollisionEventProcessorTests, Process_DifferentAngles_ShouldChangeVelocityAngleAccordingly) {
  // Arrange
  CollisionEventProcessor sut;
  std::vector<std::unique_ptr<world::Component>> components;
  auto collider = std::make_unique<BoxCollider>(world::Position(0, 0), math::Vector2D(2, 2));
  components.push_back(std::move(collider));
  auto rigidBody = std::make_unique<RigidBody>(math::Vector2D(0, 10), 1);
  components.push_back(std::move(rigidBody));
  world::Entity entity(1, std::move(components));
  // Act
  CollisionEvent const event(entity, 30, 1);
  sut.process(event);
  auto newRigidBody = entity.getComponent<RigidBody>().value().get(); // NOLINT bugprone-unchecked-optional-access
  // Assert
  EXPECT_EQ(test_utility::roundTo(newRigidBody.getVelocity().x, 6), 8.660254f);
  EXPECT_EQ(test_utility::roundTo(newRigidBody.getVelocity().y, 6), 5);
}
} // namespace pong::physics
