#include "math.hpp"
#include <vector>

namespace pong::math {

Polygon::Polygon(const std::vector<Vector2D> &vertices) : vertices(vertices) {
  if (vertices.size() < 3)
    throw std::invalid_argument("requires at least 3 vertices");
}

const std::vector<Vector2D> &Polygon::getVertices() const { return this->vertices; }

Polygon Polygon::clip(const Polygon &clip) const {
  // Sutherland-Hodgman
  std::vector<Vector2D> output = this->getVertices();
  for (int i = 0; i < clip.vertices.size(); i++) {
    std::vector<Vector2D> input = output;
    output.clear();
    Vector2D clipCurrent = clip.vertices[i];
    Vector2D clipLast = clip.vertices[(i - 1) % clip.vertices.size()];
    math::Line clipLine(clipCurrent, clipLast - clipCurrent);
    for (int j = 0; j < input.size(); j++) {
      Vector2D currentPoint = input[j];
      Vector2D lastPoint = input[(j - 1) % input.size()];
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
  // Merge vertices in each other
  for (long i = (long)output.size() - 1; i >= 0; i--) {
    auto last = (i - 1) % output.size();
    if (output[i] == output[last]) {
      output.erase(output.begin() + (long)last);
      i--;
    }
  }
  return Polygon(output);
}

bool Polygon::is_inside_edge(const Vector2D &point, const Vector2D &edgePoint1, const Vector2D &edgePoint2) const {
  Vector2D edgeVector = edgePoint2 - edgePoint1;
  Vector2D pointVector = point - edgePoint1;
  return pointVector.cross(edgeVector) <= 0;
}

} // namespace pong::math
