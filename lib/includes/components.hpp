#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <world.hpp>
#include <math.hpp>

namespace pong::world {

	class Position : public Component, public math::Vector2D {
	public:
		Position(float x, float y) : math::Vector2D(x, y) { }
	};
}

#endif