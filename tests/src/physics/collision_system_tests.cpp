#include <world_doubles.hpp>
#include <event_doubles.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <components.hpp>
#include <physics.hpp>

namespace pong::physics {

		TEST(CollisionSystemTests, Collision_ShouldPushEventForBothEntities) {
			//Arrange
			world::events::testing::SpyEventQueuePort spyEventQueue;
			CollisionSystem sut(spyEventQueue);
			std::vector<std::unique_ptr<world::Component>> components1;
			components1.push_back(std::make_unique<RigidBody>());
			components1.push_back(std::make_unique<BoxCollider>(world::Position(0, 0), math::Vector2D(2, 2)));
			world::Entity entity1(1, std::move(components1));
			std::vector<std::unique_ptr<world::Component>> components2;
			components2.push_back(std::make_unique<RigidBody>());
			components2.push_back(std::make_unique<BoxCollider>(world::Position(1, 1), math::Vector2D(2, 2)));
			world::Entity entity2(2, std::move(components2));
			//Act
			auto entities = std::vector<world::Entity>();
			entities.push_back(std::move(entity1));
			entities.push_back(std::move(entity2));
			sut.run(entities);
			//Assert
			ASSERT_EQ(spyEventQueue.getEvents().size(), 2);
		}


		TEST(CollisionSystemTests, Collision_IncludesEntityWithoutCollider_ShouldPushEventOnlyForEntitesWithColliders) {
			//Arrange
			world::events::testing::SpyEventQueuePort spyEventQueue;
			CollisionSystem sut(spyEventQueue);
			std::vector<std::unique_ptr<world::Component>> components_block;
			world::Entity entity_block(9999, std::move(components_block));
			std::vector<std::unique_ptr<world::Component>> components1;
			components1.push_back(std::make_unique<RigidBody>());
			components1.push_back(std::make_unique<BoxCollider>(world::Position(0, 0), math::Vector2D(2, 2)));
			world::Entity entity1(1, std::move(components1));
			std::vector<std::unique_ptr<world::Component>> components2;
			components2.push_back(std::make_unique<RigidBody>());
			components2.push_back(std::make_unique<BoxCollider>(world::Position(1, 1), math::Vector2D(2, 2)));
			world::Entity entity2(2, std::move(components2));
			//Act
			auto entities = std::vector<world::Entity>();
			entities.push_back(std::move(entity_block));
			entities.push_back(std::move(entity1));
			entities.push_back(std::move(entity2));
			sut.run(entities);
			//Assert
			ASSERT_EQ(spyEventQueue.getEvents().size(), 2);
		}

		//TODO: Change the collision system to use dynamic angle
		//For now uses fixed values
		TEST(CollisionSystemTests, Collision_Always_ShouldPassCollisionAngleOf90) {
			//Arrange
			world::events::testing::SpyEventQueuePort spyEventQueue;
			CollisionSystem sut(spyEventQueue);
			std::vector<std::unique_ptr<world::Component>> components1;
			components1.push_back(std::make_unique<RigidBody>());
			components1.push_back(std::make_unique<BoxCollider>(world::Position(0, 0), math::Vector2D(2, 2)));
			world::Entity entity1(1, std::move(components1));
			std::vector<std::unique_ptr<world::Component>> components2;
			components2.push_back(std::make_unique<RigidBody>());
			components2.push_back(std::make_unique<BoxCollider>(world::Position(1, 1), math::Vector2D(2, 2)));
			auto entity2 = world::Entity(2, std::move(components2));
			//Act
			auto entities = std::vector<world::Entity>();
			entities.push_back(std::move(entity1));
			entities.push_back(std::move(entity2));
			sut.run(entities);
			//Assert
			const auto& event = dynamic_cast<CollisionEvent const&>(*spyEventQueue.getEvents().front());
			EXPECT_EQ(event.getAngle(), 90);
		}
	}
