#include <physics.hpp>
#include <stdexcept>
#include <string>

namespace pong {
    namespace physics {

        CollisionEvent::CollisionEvent(std::shared_ptr<Entity> target, float angle, float bounce) 
            : target(target), angle(angle), bounce(bounce) {
        }

        std::shared_ptr<Entity> CollisionEvent::getTarget() const {
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