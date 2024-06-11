#include <cmath>
#include <events.hpp>
#include <physics.hpp>

namespace pong::physics {

void CollisionEventProcessor::process(const world::events::Event &event) {
  try {
    const auto &collision = dynamic_cast<const CollisionEvent &>(event);
    auto bodyOption = collision.getTarget().getComponent<RigidBody>();
    if (!bodyOption.has_value()) {
      return;
    }
    auto &body = bodyOption.value().get();
    auto newVelocity = calculateVelocityAfterCollision(collision.getAngle(), body, collision.getBounce());
    body.setVelocity(newVelocity);
  } catch (const std::bad_cast &) {
    // Event is of different type than required by processor.
    // Not my business, just return
    return;
  }
}

math::Vector2D CollisionEventProcessor::calculateVelocityAfterCollision(float angle, const RigidBody &targetRigidBody,
                                                                        float bounce) {
  auto rotationAngleRadian = math::toRadian(angle * 2);
  auto velocity = targetRigidBody.getVelocity();
  auto cos = std::cos(rotationAngleRadian);
  auto sin = std::sin(rotationAngleRadian);
  auto y = velocity.y * cos;
  auto x = velocity.x * sin;
  auto res = y - x;
  math::Vector2D const newVec(velocity.x * std::cos(rotationAngleRadian) + velocity.y * std::sin(rotationAngleRadian),
                              velocity.y * std::cos(rotationAngleRadian) - velocity.x * std::sin(rotationAngleRadian));
  return newVec * bounce;
}

} // namespace pong::physics
