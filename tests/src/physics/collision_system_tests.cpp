#include <world_doubles.hpp>
#include <event_doubles.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <components.hpp>
#include <physics.hpp>

using ::testing::Eq;

using namespace pong::physics;
using pong::world::Position;
using pong::world::Entity;

TEST(CollisionSystem, Collision_ShouldPushEventForBothEntities) {
	//Arrange
	auto spyEventQueue = std::make_shared<SpyEventQueuePort>();
	CollisionSystem sut(spyEventQueue);
	std::vector<std::shared_ptr<Component>> components1;
	components1.push_back(std::make_shared<RigidBody>());
	components1.push_back(std::make_shared<BoxCollider>(Position(0, 0), Vector2D(2, 2)));
	auto entity1 = std::make_shared<Entity>(1, components1);
	std::vector<std::shared_ptr<Component>> components2;
	components2.push_back(std::make_shared<RigidBody>());
	components2.push_back(std::make_shared<BoxCollider>(Position(1, 1), Vector2D(2, 2)));
	auto entity2 = std::make_shared<Entity>(2, components2);
	//Act
	sut.run(std::vector<std::shared_ptr<Entity>> { entity1, entity2 });
	//Assert
	ASSERT_EQ(spyEventQueue->getEvents()->size(), 2);
}


TEST(CollisionSystem, Collision_IncludesEntityWithoutCollider_ShouldPushEventOnlyForEntitesWithColliders) {
	//Arrange
	auto spyEventQueue = std::make_shared<SpyEventQueuePort>();
	CollisionSystem sut(spyEventQueue);
	std::vector<std::shared_ptr<Component>> components_block;
	auto entity_block = std::make_shared<Entity>(9999, components_block);
	std::vector<std::shared_ptr<Component>> components1;
	components1.push_back(std::make_shared<RigidBody>());
	components1.push_back(std::make_shared<BoxCollider>(Position(0, 0), Vector2D(2, 2)));
	auto entity1 = std::make_shared<Entity>(1, components1);
	std::vector<std::shared_ptr<Component>> components2;
	components2.push_back(std::make_shared<RigidBody>());
	components2.push_back(std::make_shared<BoxCollider>(Position(1, 1), Vector2D(2, 2)));
	auto entity2 = std::make_shared<Entity>(2, components2);
	//Act
	sut.run(std::vector<std::shared_ptr<Entity>> { entity_block, entity1, entity2 });
	//Assert
	ASSERT_EQ(spyEventQueue->getEvents()->size(), 2);
}

//TODO: Change the collision system to use dynamic angle
//For now uses fixed values
TEST(CollisionSystem, Collision_Always_ShouldPassCollisionAngleOf90) {
	//Arrange
	auto spyEventQueue = std::make_shared<SpyEventQueuePort>();
	CollisionSystem sut(spyEventQueue);
	std::vector<std::shared_ptr<Component>> components1;
	components1.push_back(std::make_shared<RigidBody>());
	components1.push_back(std::make_shared<BoxCollider>(Position(0, 0), Vector2D(2, 2)));
	auto entity1 = std::make_shared<Entity>(1, components1);
	std::vector<std::shared_ptr<Component>> components2;
	components2.push_back(std::make_shared<RigidBody>());
	components2.push_back(std::make_shared<BoxCollider>(Position(1, 1), Vector2D(2, 2)));
	auto entity2 = std::make_shared<Entity>(2, components2);
	//Act
	sut.run(std::vector<std::shared_ptr<Entity>> { entity1, entity2 });
	//Assert
	auto event = std::dynamic_pointer_cast<CollisionEvent>(spyEventQueue->getEvents()->front());
	EXPECT_EQ(event->getAngle(), 90);
}