#include <components.hpp>
#include <physics.hpp>
#include <world_doubles.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <event_doubles.hpp>

using namespace pong::physics;
using pong::world::Position;
using pong::world::Entity;

TEST(PhysicsSystemTests, Velocity_ShouldDisplaceEntity) {
	//Arrange
	ClockStub clockStub(1);
	PhysicsSystem sut(clockStub);
	std::vector<std::unique_ptr<Component>> components;
	components.push_back(std::make_unique<Position>(Position(0, 0)));
	RigidBody rigidBody;
	rigidBody.getVelocity()->x = 1;
	rigidBody.getVelocity()->y = 3;
	components.push_back(std::make_unique<RigidBody>(rigidBody));
	Entity entity(1, std::move(components));
	std::vector<Entity> entities;
	entities.push_back(std::move(entity));
	//Act
	sut.run(entities);
	//Assert
	auto& position = entities.front().getComponent<Position>().value().get();
	EXPECT_EQ(position.x, 1);
	EXPECT_EQ(position.y, 3);
}

TEST(PhysicsSystemTests, Velocity_ShouldCalculateUsingTimestemp) {
	//Arrange
	ClockStub clock(0.005f);
	PhysicsSystem sut(clock);
	std::vector<std::unique_ptr<Component>> components;
	components.push_back(std::make_unique<Position>(0, 0));
	RigidBody rigidBody;
	rigidBody.getVelocity()->x = 1;
	rigidBody.getVelocity()->y = 3;
	components.push_back(std::make_unique<RigidBody>(rigidBody));
	Entity entity(1, std::move(components));
	std::vector<Entity> entities;
	entities.push_back(std::move(entity));
	//Act
	sut.run(entities);
	//Assert
	auto& changedEntity = entities.front();
	auto& position = changedEntity.getComponent<Position>().value().get();
	EXPECT_EQ(position.x, 0.005f);
	EXPECT_EQ(position.y, 0.015f);
}