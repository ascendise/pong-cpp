#include <physics/physics.hpp>

using pong::physics::RigidBody;
using pong::math::Vector2D;


RigidBody::RigidBody() {
	this->velocity = std::make_shared<Vector2D>(std::move(Vector2D(0, 0)));
}

std::shared_ptr<Vector2D> RigidBody::getVelocity() {
	return this->velocity;
}