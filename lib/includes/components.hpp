#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include "world.hpp"
#include <math.hpp>

namespace pong {
	namespace world {

		class Position : public Component, public math::Vector2D 
		{
		public:
			Position(int x, int y) : math::Vector2D(x, y) { }
		};

	}
}

#endif