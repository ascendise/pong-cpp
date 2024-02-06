#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <math.hpp>
#include <world.hpp>

namespace pong::world {

/// @see Component that stores the @see Position of the @see Entity in 2D Space
class Position : public Component, public math::Vector2D {
public:
  Position(float x, float y) : math::Vector2D(x, y) {}
};

} // namespace pong::world

#endif
