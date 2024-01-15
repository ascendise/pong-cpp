#include <physics.hpp>

using pong::physics::RigidBody;
using pong::math::Vector2D;

float RigidBody::getBounce() {
	return this->bounce;
}

void RigidBody::setBounce(float bounce) {
	this->bounce = bounce;
}

void RigidBody::setVelocity(Vector2D v) {
	this->velocity = v;
}

Vector2D& RigidBody::getVelocity() {
	return this->velocity;
}