#include <world/components.hpp>
#include <physics/physics.hpp>
#include "test_doubles/stub/clock_stub.cpp"
#include <gtest/gtest.h>
#include <memory>

using pong::physics::PhysicsSystem;
using pong::physics::RigidBody;
using pong::world::Position;
using pong::world::Entity;
using pong::world::ClockStub;

TEST(PhysicsSystem, Velocity_ShouldDisplaceEntity) {
	//Arrange
	PhysicsSystem sut(std::make_shared<ClockStub>(ClockStub(1)));
	std::vector<std::shared_ptr<Component>> components;
	components.push_back(std::make_shared<Position>(Position(0, 0)));
	RigidBody rigidBody;
	rigidBody.getVelocity()->x = 1;
	rigidBody.getVelocity()->y = 3;
	components.push_back(std::make_shared<RigidBody>(rigidBody));
	Entity entity(1, components);
	std::vector<std::shared_ptr<Entity>> entities;
	entities.push_back(std::make_shared<Entity>(entity));
	//Act
	sut.run(entities);
	//Assert
	Position* position = entity.getComponent<Position>().get();
	EXPECT_EQ(position->x, 1);
	EXPECT_EQ(position->y, 3);
}

TEST(PhysicsTests, Velocity_ShouldCalculateUsingTimestemp) {
	//Arrange
	PhysicsSystem sut(std::make_shared<ClockStub>(ClockStub(0.005f)));
	std::vector<std::shared_ptr<Component>> components;
	components.push_back(std::make_shared<Position>(Position(0, 0)));
	RigidBody rigidBody;
	rigidBody.getVelocity()->x = 1;
	rigidBody.getVelocity()->y = 3;
	components.push_back(std::make_shared<RigidBody>(rigidBody));
	Entity entity(1, components);
	std::vector<std::shared_ptr<Entity>> entities;
	entities.push_back(std::make_shared<Entity>(entity));
	//Act
	sut.run(entities);
	//Assert
	Position* position = entity.getComponent<Position>().get();
	EXPECT_EQ(position->x, 0.005f);
	EXPECT_EQ(position->y, 0.015f);
}