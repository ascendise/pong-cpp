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
  for (int i = 1; i <= clip.vertices.size(); i++) {
    math::Vector2D clipVertex1 = clip.vertices[i - 1];
    math::Vector2D clipVertex2 = clip.vertices[i];
    if (i == clip.vertices.size())
      clipVertex2 = clip.vertices[0];
    math::Line clipLine(clipVertex1, clipVertex2 - clipVertex1);
    for (int y = 1; y <= this->vertices.size(); y++) {
      math::Vector2D srcVertex1 = this->vertices[y - 1];
      math::Vector2D srcVertex2 = this->vertices[y];
      if (y == this->vertices.size())
        srcVertex2 = this->vertices[0];
      math::Line srcLine(srcVertex1, srcVertex2 - srcVertex1);
      auto intersect = clipLine.findIntersect(srcLine);
      if (intersect.has_value()) {
        intersections.push_back(*intersect);
      }
    }
  }
  return Polygon(intersections);
}

} // namespace pong::physics
