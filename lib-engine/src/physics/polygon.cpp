#include "math.hpp"
#include <physics.hpp>
#include <vector>

namespace pong::physics {

Polygon::Polygon(const std::vector<math::Vector2D> &vertices) : vertices(vertices) {
  if (vertices.size() < 3)
    throw std::invalid_argument("requires at least 3 vertices");
}

const std::vector<math::Vector2D> &Polygon::getVertices() const { return this->vertices; }

Polygon Polygon::clip(const Polygon &clip) const {
  std::vector<math::Vector2D> intersections;
  for (int i = 0; i < clip.vertices.size(); i++) {
    int i1 = i;
    int i2 = i + 1;
    if (i2 == clip.vertices.size())
      i2 = 0;
    math::Edge edge(clip.vertices[i1], clip.vertices[i2]);
    for (const auto &vertex : this->vertices) {
      math::Vector2D point = edge.solvePoint(vertex.x);
      if (point == vertex)
        intersections.push_back(vertex);
    }
  }
}

} // namespace pong::physics
