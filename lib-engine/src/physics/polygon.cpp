#include "math.hpp"
#include <physics.hpp>
#include <vector>

namespace pong::physics {

Polygon::Polygon(std::vector<math::Vector2D> vertices) : vertices(vertices) {
  if (vertices.size() < 3)
    throw std::invalid_argument("requires at least 3 vertices");
}

const std::vector<math::Vector2D> &Polygon::getVertices() const { return this->vertices; }

Polygon Polygon::clip(const Polygon &clippingPolygon) const {
  std::vector<math::Vector2D> vertices = {
      math::Vector2D(0.0f, 0.0f),
      math::Vector2D(0.0f, 0.0f),
      math::Vector2D(0.0f, 0.0f),
      math::Vector2D(0.0f, 0.0f),
  };
  return Polygon(std::vector<math::Vector2D>(vertices));
}

} // namespace pong::physics
