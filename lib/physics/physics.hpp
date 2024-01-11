#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "../world/world.hpp"
#include "../rendering/rendering.hpp"
#include "../math.hpp"
#include "../world/components.hpp"

using namespace pong::world;
using namespace pong::world::events;
using pong::math::Vector2D;

namespace pong {
	namespace physics {

		class PhysicsSystem : public System 
		{
		private:
			std::shared_ptr<IReadOnlyClock> clock;
		public:
			PhysicsSystem(std::shared_ptr<IReadOnlyClock> clock);
			void run(std::vector<std::shared_ptr<Entity>> entities);
		};

		class RigidBody : public Component {
		private:
			std::shared_ptr<Vector2D> velocity;
			float bounce;
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
				std::shared_ptr<Entity> target;
				float angle;
				float bounce;
			public:
				CollisionEvent(std::shared_ptr<Entity> target, float angle, float bounce);
				std::shared_ptr<Entity> getTarget() const;
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
			void process(std::shared_ptr<Event> event);
		};

		class CollisionSystem : public System {
		private:
			std::shared_ptr<IEventQueuePort> eventQueue;
			void pushCollisionEvent(std::shared_ptr<Entity> target, std::shared_ptr<Entity> hurdle);
			float getAngle(std::shared_ptr<Entity> target, std::shared_ptr<BoxCollider> hurdleCollider);
		public:
			CollisionSystem(std::shared_ptr<IEventQueuePort> eventQueue);
			void run(std::vector<std::shared_ptr<Entity>> entities);
		};
	}
}

#endif