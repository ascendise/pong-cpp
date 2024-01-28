#include <events.hpp>
#include <physics.hpp>
#include <utility>
#include <world.hpp>

namespace pong::physics {

void CollisionSystem::run(std::vector<world::Entity> &entities) {
  auto collisions = findCollisions(entities);
  for (auto &collision : collisions) {
    pushCollisionEvent(collision.entity1, collision.entity2);
    pushCollisionEvent(collision.entity2, collision.entity1);
  }
}

std::vector<Collision> CollisionSystem::findCollisions(std::vector<world::Entity> &entities) {
  std::vector<Collision> collisions;
  for (int i = 0; i <= entities.size() - 2; i++) {
    auto &target = entities[i];
    auto targetColliderOption = target.getComponent<BoxCollider>();
    if (!targetColliderOption.has_value())
      continue;
    auto &targetCollider = targetColliderOption.value().get();
    for (int y = i + 1; y <= entities.size() - 1; y++) {
      auto &hurdle = entities[y];
      auto hurdleCollider = hurdle.getComponent<BoxCollider>();
      if (hurdleCollider.has_value() && targetCollider.intersects(hurdleCollider.value().get())) {
        Collision const collision(target, hurdle);
        collisions.push_back(collision);
      }
    }
  }
  return collisions;
}

void CollisionSystem::pushCollisionEvent(world::Entity &target, world::Entity &hurdle) {
  auto hurdleRigidBodyOption = hurdle.getComponent<RigidBody>();
  auto bounce = hurdleRigidBodyOption.has_value() ? hurdleRigidBodyOption.value().get().getBounce() : 0;
  eventQueue.enqueue(std::make_shared<CollisionEvent>(target, 90, bounce));
}
} // namespace pong::physics
