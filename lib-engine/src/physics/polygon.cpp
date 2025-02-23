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
    math::Vector2D vertex1 = clip.vertices[i1];
    math::Vector2D vertex2 = clip.vertices[i2];
    math::Vector2D edge(vertex2.x - vertex1.x, vertex2.y - vertex1.y);
    for (const auto &vertex : this->vertices) {
      math::Vector2D positionVector(vertex1.x + edge.x, vertex1.y + edge.y);
      if (positionVector.normalize() == edge.normalize())
        intersections.push_back(vertex);
    }
  }
}

} // namespace pong::physics
