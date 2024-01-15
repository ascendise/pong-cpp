#include "physics.hpp"
#include <events.hpp>
#include <cmath>


namespace pong {
    namespace physics {

        math::Vector2D calculateVelocityAfterCollision(const CollisionEvent& e);
        
        void CollisionEventProcessor::process(world::events::Event& event) {
            try {
                auto& collision = dynamic_cast<CollisionEvent&>(event);
                auto bodyOption = collision.getTarget().getComponent<RigidBody>();
                if (!bodyOption.has_value()) {
                    return;
                }
                auto& body = bodyOption.value().get();
                auto newVelocity = calculateVelocityAfterCollision(collision);
                body.setVelocity(newVelocity);
            }
            catch (const std::bad_cast&) {
                //Event is of different type than required by processor.
                //Not my business, just return
                return;
            }
        }

        math::Vector2D calculateVelocityAfterCollision(const CollisionEvent& e) { 
            auto rotationAngleRadian = pong::math::toRadian(e.getAngle() * 2);
            auto targetRigidBodyOption = e.getTarget().getComponent<RigidBody>();
            auto& targetRigidBody = targetRigidBodyOption.value().get();
            auto velocity = targetRigidBody.getVelocity();
            auto cos = std::cos(rotationAngleRadian);
            auto sin = std::sin(rotationAngleRadian);
            auto y = velocity.y * cos;
            auto x = velocity.x * sin;
            auto res = y - x;
            math::Vector2D newVec(
                velocity.x * std::cos(rotationAngleRadian) + velocity.y * std::sin(rotationAngleRadian),
                velocity.y * std::cos(rotationAngleRadian) - velocity.x * std::sin(rotationAngleRadian)
            );
            return newVec * e.getBounce();
        }

    }
}