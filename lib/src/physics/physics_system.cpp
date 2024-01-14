#include <physics.hpp>
#include <components.hpp>
#include <stdexcept>
#include <iostream>

using pong::physics::PhysicsSystem;
using pong::physics::RigidBody;
using pong::world::Entity;
using pong::world::Position;

void PhysicsSystem::run(std::vector<Entity>& entities) {
	for (int i = 0; i <= entities.size() - 1; i++) {
		auto& entity = entities[i];
		auto positionOption = entity.getComponent<Position>();
		auto rigidBodyOption = entity.getComponent<RigidBody>();
		if(positionOption.has_value() && rigidBodyOption.has_value()) {
			auto& position = positionOption.value().get();
			auto& rigidBody = rigidBodyOption.value().get();
			auto positionDifference = *rigidBody.getVelocity() * clock.getFrameTimeDelta();
			position += positionDifference;
			auto colliderOption = entity.getComponent<BoxCollider>();
			if (colliderOption.has_value()) {
				*colliderOption.value().get().getPosition() += positionDifference;
			}
		}
	}
}