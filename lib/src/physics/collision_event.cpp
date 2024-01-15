#include <physics.hpp>
#include <stdexcept>
#include <string>

namespace pong {
    namespace physics {

        Entity& CollisionEvent::getTarget() const {
            return this->target;
        }

        float CollisionEvent::getAngle() const {
            return this->angle;
        }

        float CollisionEvent::getBounce() const {
            return this->bounce;
        }


    }
}