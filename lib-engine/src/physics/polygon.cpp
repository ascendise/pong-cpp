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
  std::vector<math::Vector2D> output = this->getVertices();
  for (int i = 0; i < clip.vertices.size(); i++) {
    std::vector<math::Vector2D> input = output;
    output.clear();
    math::Vector2D clipCurrent = clip.vertices[i];
    math::Vector2D clipLast = clip.vertices[(i - 1) % clip.vertices.size()];
    math::Line clipLine(clipCurrent, clipLast - clipCurrent);
    for (int j = 0; j < input.size(); j++) {
      math::Vector2D currentPoint = input[j];
      math::Vector2D lastPoint = input[(j - 1) % input.size()];
      math::Line edge(currentPoint, lastPoint - currentPoint);
      auto intersect = clipLine.findIntersectInfinite(edge);
      if (is_inside_edge(currentPoint, clipLast, clipCurrent)) {
        if (!is_inside_edge(lastPoint, clipLast, clipCurrent))
          output.push_back(*intersect);
        output.push_back(currentPoint);
      } else if (is_inside_edge(lastPoint, clipLast, clipCurrent)) {
        output.push_back(*intersect);
      }
    }
  }
  return Polygon(output);
}

bool Polygon::is_inside_edge(const math::Vector2D &point, const math::Vector2D &edgePoint1,
                             const math::Vector2D &edgePoint2) const {
  math::Vector2D edgeVector = edgePoint2 - edgePoint1;
  math::Vector2D pointVector = point - edgePoint1;
  return pointVector.cross(edgeVector) <= 0;
}

} // namespace pong::physics
