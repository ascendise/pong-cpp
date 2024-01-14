#include <world.hpp>
#include <physics.hpp>
#include <events.hpp>

using namespace pong::world;
using namespace pong::world::events;
using namespace pong::physics;

void CollisionSystem::run(std::vector<Entity>& entities) {
	for (int i = 0; i <= entities.size() - 2; i++) {
		auto& target = entities[i];
		auto targetColliderOption = target.getComponent<BoxCollider>();
		if (!targetColliderOption.has_value()) 
			continue;
		auto& targetCollider = targetColliderOption.value().get();
		for (int y = i + 1; y <= entities.size() - 1; y++) {
			auto& hurdle = entities[y];
			auto hurdleCollider = hurdle.getComponent<BoxCollider>();
			if (hurdleCollider.has_value() && targetCollider.intersects(hurdleCollider.value().get())) {
				pushCollisionEvent(target, hurdle);
				pushCollisionEvent(hurdle, target);
			}
		}
	}
}

void CollisionSystem::pushCollisionEvent(Entity& target, Entity& hurdle) {
	auto hurdleRigidBodyOption = hurdle.getComponent<RigidBody>();
	auto bounce = hurdleRigidBodyOption.has_value() ? hurdleRigidBodyOption.value().get().getBounce() : 0;
	eventQueue.enqueue(std::make_shared<CollisionEvent>(target, 90, bounce));
}