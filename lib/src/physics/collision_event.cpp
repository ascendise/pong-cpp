#include <physics.hpp>
#include <stdexcept>
#include <string>

namespace pong::physics {

	world::Entity& CollisionEvent::getTarget() const {
		return this->target;
    }

    float CollisionEvent::getAngle() const {
        return this->angle;
    }

    float CollisionEvent::getBounce() const {
        return this->bounce;
   	} 


}
