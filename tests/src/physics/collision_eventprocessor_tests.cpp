#include <math.hpp>
#include <physics.hpp>
#include <test_utility.hpp>

#include <gtest/gtest.h>

namespace pong::physics {

TEST(CollisionEventProcessorTests, Process_FrontalCollisionAgainstStaticObject_ShouldChangeVelocityOfEntity) {
  // Arrange
  CollisionEventProcessor sut;
  std::vector<std::shared_ptr<world::Component>> components;
  auto collider = std::make_unique<BoxCollider>(world::Position(0.0f, 0.0f), math::Vector2D(2.0f, 2.0f));
  components.push_back(std::move(collider));
  auto rigidBody = std::make_unique<RigidBody>(math::Vector2D(1.0f, 0.0f), 1.0f);
  components.push_back(std::move(rigidBody));
  world::Entity entity(1, components);
  // Act
  CollisionEvent const event(entity, 90.0f, 1.0f);
  sut.process(event);
  // Assert
  auto &newRigidbody = entity.getComponent<RigidBody>().value().get(); // NOLINT bugprone-unchecked-optional-access
  EXPECT_EQ(newRigidbody.getVelocity().x, -1.0f);
  EXPECT_EQ(test_utility::roundTo(newRigidbody.getVelocity().y, 4.0f), 0.0f);
}

TEST(CollisionEventProcessorTests, Process_FrontalCollisionAgainstStickyObject_ShouldSlowVelocityOfEntity1) {
  // Arrange
  CollisionEventProcessor sut;
  std::vector<std::shared_ptr<world::Component>> components;
  auto collider = std::make_unique<BoxCollider>(world::Position(0.0f, 0.0f), math::Vector2D(2.0f, 2.0f));
  components.push_back(std::move(collider));
  auto rigidBody = std::make_unique<RigidBody>(math::Vector2D(1.0f, 0.0f), 1.0f);
  components.push_back(std::move(rigidBody));
  world::Entity entity(1, components);
  // Act
  CollisionEvent const event(entity, 90.0f, 0.5f);
  sut.process(event);
  // Assert
  auto &newRigidbody = entity.getComponent<RigidBody>().value().get(); // NOLINT bugprone-unchecked-optional-access
  EXPECT_EQ(newRigidbody.getVelocity().x, -0.5f);
  EXPECT_EQ(test_utility::roundTo(newRigidbody.getVelocity().y, 4.0f), 0.0f);
}

TEST(CollisionEventProcessorTests, Process_FrontalCollisionAgainstStickyObject_ShouldSlowVelocityOfEntity2) {
  // Arrange
  CollisionEventProcessor sut;
  std::vector<std::shared_ptr<world::Component>> components;
  auto collider = std::make_unique<BoxCollider>(world::Position(0.0f, 0.0f), math::Vector2D(2.0f, 2.0f));
  components.push_back(std::move(collider));
  auto rigidBody = std::make_unique<RigidBody>(math::Vector2D(10.0f, 0.0f), 1.0f);
  components.push_back(std::move(rigidBody));
  world::Entity entity(1, components);
  // Act
  CollisionEvent const event(entity, 90.0f, 0.2f);
  sut.process(event);
  // Assert
  auto &newRigidBody = entity.getComponent<RigidBody>().value().get(); // NOLINT bugprone-unchecked-optional-access
  EXPECT_EQ(newRigidBody.getVelocity().x, -2.0f);
  EXPECT_EQ(test_utility::roundTo(newRigidBody.getVelocity().y, 4.0f), 0.0f);
}

TEST(CollisionEventProcessorTests, Process_DifferentAngles_ShouldChangeVelocityAngleAccordingly) {
  // Arrange
  CollisionEventProcessor sut;
  std::vector<std::shared_ptr<world::Component>> components;
  auto collider = std::make_unique<BoxCollider>(world::Position(0.0f, 0.0f), math::Vector2D(2.0f, 2.0f));
  components.push_back(std::move(collider));
  auto rigidBody = std::make_unique<RigidBody>(math::Vector2D(0, 10), 1.0f);
  components.push_back(std::move(rigidBody));
  world::Entity entity(1, components);
  // Act
  CollisionEvent const event(entity, 30.0f, 1.0f);
  sut.process(event);
  auto &newRigidBody = entity.getComponent<RigidBody>().value().get(); // NOLINT bugprone-unchecked-optional-access
  // Assert
  EXPECT_EQ(test_utility::roundTo(newRigidBody.getVelocity().x, 6.0f), 8.660254f);
  EXPECT_EQ(test_utility::roundTo(newRigidBody.getVelocity().y, 6.0f), 5.0f);
}

} // namespace pong::physics
