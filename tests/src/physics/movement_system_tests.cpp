#include <components.hpp>
#include <gtest/gtest.h>
#include <math.hpp>
#include <memory>
#include <physics.hpp>
#include <world_doubles.hpp>

namespace pong::physics {

TEST(MovementSystemTests, Velocity_ShouldDisplaceEntity) {
  // Arrange
  world::testing::ClockStub clockStub(1);
  MovementSystem sut(clockStub);
  std::vector<std::shared_ptr<world::Component>> components;
  components.push_back(std::make_shared<world::Position>(0, 0));
  RigidBody const rigidBody(math::Vector2D(1, 3), 1);
  components.push_back(std::make_shared<RigidBody>(rigidBody));
  world::Entity entity(1, components);
  std::vector<world::Entity> entities;
  entities.push_back(std::move(entity));
  // Act
  sut.run(entities);
  // Assert
  auto positionOption = entities.front().getComponent<world::Position>();
  auto &position = positionOption.value().get(); // NOLINT bugprone-unchecked-optional-access
  EXPECT_EQ(position.x, 1);
  EXPECT_EQ(position.y, 3);
}

TEST(MovementSystemTests, Velocity_ShouldCalculateUsingTimestemp) {
  // Arrange
  world::testing::ClockStub clock(0.005f);
  MovementSystem sut(clock);
  std::vector<std::shared_ptr<world::Component>> components;
  components.push_back(std::make_shared<world::Position>(0, 0));
  RigidBody const rigidBody(math::Vector2D(1, 3), 1);
  components.push_back(std::make_shared<RigidBody>(rigidBody));
  world::Entity entity(1, components);
  std::vector<world::Entity> entities;
  entities.push_back(std::move(entity));
  // Act
  sut.run(entities);
  // Assert
  auto &changedEntity = entities.front();
  auto position =
      changedEntity.getComponent<world::Position>().value().get(); // NOLINT bugprone-unchecked-optional-access
  EXPECT_EQ(position.x, 0.005f);
  EXPECT_EQ(position.y, 0.015f);
}

TEST(MovementSystemTests, EntityHasColliders_ShouldDisplaceCollider) {
  // Arrange
  world::testing::ClockStub clockStub(1);
  MovementSystem sut(clockStub);
  std::vector<std::shared_ptr<world::Component>> components;
  components.push_back(std::make_shared<world::Position>(0, 0));
  components.push_back(std::make_shared<RigidBody>(math::Vector2D(1, 3), 1));
  components.push_back(std::make_shared<BoxCollider>(world::Position(1, 1), math::Vector2D(5, 10)));
  world::Entity entity(1, components);
  std::vector<world::Entity> entities;
  entities.push_back(std::move(entity));
  // Act
  sut.run(entities);
  // Assert
  auto colliderOption = entities.front().getComponent<BoxCollider>();
  auto colliderPosition = colliderOption.value().get().getPosition(); // NOLINT bugprone-unchecked-optional-access
  EXPECT_EQ(colliderPosition.x, 2);
  EXPECT_EQ(colliderPosition.y, 4);
}

} // namespace pong::physics
