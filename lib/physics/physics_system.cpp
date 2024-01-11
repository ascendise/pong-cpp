#include <physics/physics.hpp>
#include <world/components.hpp>
#include <stdexcept>
#include <iostream>

using pong::physics::PhysicsSystem;
using pong::physics::RigidBody;
using pong::world::Entity;
using pong::world::Position;

PhysicsSystem::PhysicsSystem(std::shared_ptr<IReadOnlyClock> clock) {
	this->clock = clock;
}

void PhysicsSystem::run(std::vector<std::shared_ptr<Entity>> entities) {
	for (int i = 0; i <= entities.size() - 1; i++) {
		auto& entity = entities[i];
		auto position = entity->getComponent<Position>();
		auto rigidBody = entity->getComponent<RigidBody>();
		if(position && rigidBody) {
			auto positionDifference = *rigidBody->getVelocity() * clock->getFrameTimeDelta();
			*position += positionDifference;
			auto collider = entity->getComponent<BoxCollider>();
			if (collider) {
				*collider->getPosition() += positionDifference;
			}
		}
	}
}