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
    math::Vector2D clipCurrent = clip.vertices[i];
    math::Vector2D clipLast = clip.vertices[(i - 1) % clip.vertices.size()];
    math::Line clipLine(clipCurrent, clipLast - clipCurrent);
    for (int j = 0; j < this->vertices.size(); j++) {
      math::Vector2D currentPoint = this->vertices[j];
      math::Vector2D lastPoint = this->vertices[(j - 1) % this->vertices.size()];
      math::Line edge(currentPoint, lastPoint - currentPoint);
      auto intersect = clipLine.findIntersect(edge);
      if (!intersect.has_value())
        continue;
    }
  }
  return Polygon(intersections);
}

bool Polygon::point_is_inside_polygon(const math::Vector2D &point, const math::Vector2D &edgePoint1,
                                      const math::Vector2D &edgePoint2) const {}

} // namespace pong::physics
