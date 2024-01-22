#include <physics.hpp>


namespace pong::physics {

		float RigidBody::getBounce() const {
			return this->bounce;
		}

		void RigidBody::setBounce(float bounce) {
			this->bounce = bounce;
		}

		void RigidBody::setVelocity(math::Vector2D velocity) {
			this->velocity = velocity;
		}

		math::Vector2D RigidBody::getVelocity() const {
			return this->velocity;
		}
	}

