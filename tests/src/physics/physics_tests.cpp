#include <math.hpp>
#include <components.hpp>
#include <physics.hpp>
#include <world_doubles.hpp>
#include <memory>
#include <gtest/gtest.h>

namespace pong::physics {

		TEST(PhysicsSystemTests, Velocity_ShouldDisplaceEntity) {
			//Arrange
			world::testing::ClockStub clockStub(1);
			MovementSystem sut(clockStub);
			std::vector<std::unique_ptr<world::Component>> components;
			components.push_back(std::make_unique<world::Position>(world::Position(0, 0)));
			RigidBody rigidBody(math::Vector2D(1, 3), 1);
			components.push_back(std::make_unique<RigidBody>(rigidBody));
			world::Entity entity(1, std::move(components));
			std::vector<world::Entity> entities;
			entities.push_back(std::move(entity));
			//Act
			sut.run(entities);
			//Assert
			auto positionOption = entities.front().getComponent<world::Position>();
			auto& position = positionOption.value().get(); //NOLINT bugprone-unchecked-optional-access
			EXPECT_EQ(position.x, 1);
			EXPECT_EQ(position.y, 3);
		}

		TEST(PhysicsSystemTests, Velocity_ShouldCalculateUsingTimestemp) {
			//Arrange
			world::testing::ClockStub clock(0.005f);
			MovementSystem sut(clock);
			std::vector<std::unique_ptr<world::Component>> components;
			components.push_back(std::make_unique<world::Position>(0, 0));
			RigidBody rigidBody(math::Vector2D(1, 3), 1);
			components.push_back(std::make_unique<RigidBody>(rigidBody));
			world::Entity entity(1, std::move(components));
			std::vector<world::Entity> entities;
			entities.push_back(std::move(entity));
			//Act
			sut.run(entities);
			//Assert
			auto& changedEntity = entities.front();
			auto& position = changedEntity.getComponent<world::Position>().value().get(); //NOLINT bugprone-unchecked-optional-access
			EXPECT_EQ(position.x, 0.005f);
			EXPECT_EQ(position.y, 0.015f);
		}
	}

