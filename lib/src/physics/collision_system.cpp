#include <world.hpp>
#include <physics.hpp>
#include <events.hpp>

using namespace pong::world;
using namespace pong::world::events;
using namespace pong::physics;

CollisionSystem::CollisionSystem(std::shared_ptr<IEventQueuePort> eventQueue) {
	this->eventQueue = eventQueue;
}

void CollisionSystem::run(std::vector<std::shared_ptr<Entity>> entities) {
	for (int i = 0; i <= entities.size() - 2; i++) {
		auto& target = entities[i];
		auto targetCollider = target->getComponent<BoxCollider>();
		if (!targetCollider) 
			continue;
		for (int y = i + 1; y <= entities.size() - 1; y++) {
			auto& hurdle = entities[y];
			auto hurdleCollider = hurdle->getComponent<BoxCollider>();
			if (hurdleCollider && targetCollider->intersects(*hurdleCollider)) {
				pushCollisionEvent(target, hurdle);
				pushCollisionEvent(hurdle, target);
			}
		}
	}
}

void CollisionSystem::pushCollisionEvent(std::shared_ptr<Entity> target, std::shared_ptr<Entity> hurdle) {
	auto hurdleRigidBody = hurdle->getComponent<RigidBody>();
	auto targetRigidBody = target->getComponent<RigidBody>();
	auto bounce = hurdleRigidBody ? hurdleRigidBody->getBounce() : 0;
	eventQueue->enqueue(std::make_shared<CollisionEvent>(target, 90, bounce));
}