#include <physics.hpp>


namespace pong {
	namespace physics {

		float RigidBody::getBounce() {
			return this->bounce;
		}

		void RigidBody::setBounce(float bounce) {
			this->bounce = bounce;
		}

		void RigidBody::setVelocity(math::Vector2D v) {
			this->velocity = v;
		}

		math::Vector2D& RigidBody::getVelocity() {
			return this->velocity;
		}
	}
}

