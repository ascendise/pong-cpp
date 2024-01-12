#include "physics.hpp"
#include <events.hpp>
#include <cmath>

using pong::world::events::Event;

namespace pong {
    namespace physics {

        Vector2D calculateVelocityAfterCollision(const CollisionEvent& e);
        
        void CollisionEventProcessor::process(std::shared_ptr<Event> event) {
            auto collision = std::dynamic_pointer_cast<CollisionEvent>(event);
            if (collision == nullptr) {
                return;
            }
            auto body = collision->getTarget()->getComponent<RigidBody>();
            if (body == nullptr) {
                return;
            }
            auto newVelocity = calculateVelocityAfterCollision(*collision);
            body->setVelocity(newVelocity);
        }

        Vector2D calculateVelocityAfterCollision(const CollisionEvent& e) { 
            auto rotationAngleRadian = pong::math::toRadian(e.getAngle() * 2);
            auto velocity = e.getTarget()->getComponent<RigidBody>()->getVelocity();
            auto cos = std::cos(rotationAngleRadian);
            auto sin = std::sin(rotationAngleRadian);
            auto y = velocity->y * cos;
            auto x = velocity->x * sin;
            auto res = y - x;
            Vector2D newVec(
                velocity->x * std::cos(rotationAngleRadian) + velocity->y * std::sin(rotationAngleRadian),
                velocity->y * std::cos(rotationAngleRadian) - velocity->x * std::sin(rotationAngleRadian)
            );
            return newVec * e.getBounce();
        }

    }
}