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
	for(auto& entity : entities) {
		auto position = entity->getComponent<Position>();
		auto rigidBody = entity->getComponent<RigidBody>();
		if(position && rigidBody) {
			*position += *rigidBody->getVelocity() * clock->getFrameTimeDelta();
			std::cout << position->x << " " << position->y << std::endl;
		}
	}
}