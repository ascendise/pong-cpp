#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <world.hpp>
#include <rendering.hpp>
#include <math.hpp>
#include <components.hpp>

using namespace pong::world;
using namespace pong::world::events;
using pong::math::Vector2D;

namespace pong {
	namespace physics {

		class PhysicsSystem : public System 
		{
		private:
			IReadOnlyClock& clock;
		public:
			PhysicsSystem(IReadOnlyClock& clock) : clock(clock) {}
			void run(std::vector<Entity>& entities);
		};

		class RigidBody : public Component {
		private:
			std::shared_ptr<Vector2D> velocity;
			float bounce = 1;
		public:
			RigidBody();
			void setVelocity(Vector2D v);
			std::shared_ptr<Vector2D> getVelocity();
			void setBounce(float bounce);
			float getBounce();
		};

		class BoxCollider : public Component {
		private:
			std::shared_ptr<Position> position;
			std::shared_ptr<Vector2D> area;
		public:
			BoxCollider(Position position, Vector2D area);
			std::shared_ptr<Position> getPosition();
			std::shared_ptr<Vector2D> getArea();
			bool intersects(const BoxCollider& collider);
		};

		class CollisionEvent : public Event {
			private: 
				Entity& target;
				float angle;
				float bounce;
			public:
				CollisionEvent(Entity& target, float angle, float bounce)
					: target(target), angle(angle), bounce(bounce) {}
				Entity& getTarget() const;
				float getAngle() const;
				/// <summary>
				/// Returns how bouncy the surface is the target hit.
				/// 1 -> bouncy; target returns with full speed
				/// 0.5 -> target returns with half speed
				/// 0 -> target stops
				/// </summary>
				/// <returns></returns>
				float getBounce() const;
		};

		class CollisionEventProcessor : public EventProcessor {
		public:
			void process(Event& event);
		};

		class CollisionSystem : public System {
		private:
			IEventQueuePort& eventQueue;
			void pushCollisionEvent(Entity& target, Entity& hurdle);
		public:
			CollisionSystem(IEventQueuePort& eventQueue) : eventQueue(eventQueue) {}
			void run(std::vector<Entity>& entities);
		};
	}
}

#endif