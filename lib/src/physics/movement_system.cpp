#include <components.hpp>
#include <iostream>
#include <physics.hpp>
#include <stdexcept>

namespace pong::physics {

void pong::physics::MovementSystem::run(std::vector<world::Entity> &entities) {
  for (int i = 0; i <= entities.size() - 1; i++) {
    auto &entity = entities[i];
    auto positionOption = entity.getComponent<world::Position>();
    auto rigidBodyOption = entity.getComponent<RigidBody>();
    if (positionOption.has_value() && rigidBodyOption.has_value()) {
      auto &position = positionOption.value().get();
      auto &rigidBody = rigidBodyOption.value().get();
      auto positionDifference = rigidBody.getVelocity() * clock.getFrameTimeDelta();
      position += positionDifference;
      auto colliderOption = entity.getComponent<BoxCollider>();
      if (colliderOption.has_value()) {
        auto &collider = colliderOption.value().get();
        auto newColliderPosition = collider.getPosition() + positionDifference;
        collider.setPosition(world::Position(newColliderPosition.x, newColliderPosition.y));
      }
    }
  }
}

} // namespace pong::physics
