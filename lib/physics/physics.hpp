#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <world/world.hpp>
#include <math.hpp>

using pong::world::System;
using pong::world::Component;
using pong::world::Entity;
using pong::world::IReadOnlyClock;
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
	}
}

#endif