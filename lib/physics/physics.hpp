#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "../world/world.hpp"
#include "../rendering/rendering.hpp"
#include "../math.hpp"
#include "../world/components.hpp"

using pong::world::System;
using pong::world::Component;
using pong::world::Entity;
using pong::world::IReadOnlyClock;
using pong::world::Position;
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
		public:
			RigidBody();
			std::shared_ptr<Vector2D> getVelocity();
		};

		class BoxCollider : public Component {
		private:
			std::unique_ptr<Position> position;
			std::unique_ptr<Vector2D> area;
		public:
			BoxCollider(Position position, Vector2D area);
			Position getPosition();
			Vector2D getArea();
			bool intersects(const BoxCollider& collider);
		};
	}
}

#endif