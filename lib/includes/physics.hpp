#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <world.hpp>
#include <components.hpp>
#include <rendering.hpp>
#include <math.hpp>

namespace pong {
	namespace physics {

		class PhysicsSystem : public world::System 
		{
		private:
			world::IReadOnlyClock& clock;
		public:
			PhysicsSystem(world::IReadOnlyClock& clock) : clock(clock) {}
			void run(std::vector<world::Entity>& entities);
		};

		class RigidBody : public world::Component {
		private:
			math::Vector2D velocity;
			float bounce = 1;
		public:
			RigidBody(): velocity(math::Vector2D(0,0)) {}
			void setVelocity(math::Vector2D v);
			math::Vector2D& getVelocity();
			void setBounce(float bounce);
			float getBounce();
		};

		class BoxCollider : public world::Component {
		private:
			world::Position position;
			math::Vector2D area;
		public:
			BoxCollider(world::Position position, math::Vector2D area):
				position(position), area(area) {}
			world::Position& getPosition();
			math::Vector2D& getArea();
			bool intersects(const BoxCollider& collider);
		};

		class CollisionEvent : public world::events::Event {
			private: 
				world::Entity& target;
				float angle;
				float bounce;
			public:
				CollisionEvent(world::Entity& target, float angle, float bounce)
					: target(target), angle(angle), bounce(bounce) {}
				world::Entity& getTarget() const;
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

		class CollisionEventProcessor : public world::events::EventProcessor{
		public:
			void process(world::events::Event& event);
		};

		class CollisionSystem : public world::System {
		private:
			world::events::IEventQueuePort& eventQueue;
			void pushCollisionEvent(world::Entity& target, world::Entity& hurdle);
		public:
			CollisionSystem(world::events::IEventQueuePort& eventQueue) : eventQueue(eventQueue) {}
			void run(std::vector<world::Entity>& entities);
		};
	}
}

#endif