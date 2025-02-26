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
    math::Vector2D clipVertex1 = clip.vertices[i1];
    math::Vector2D clipVertex2 = clip.vertices[i2];
    math::Line clipLine(clipVertex1, clipVertex2 - clipVertex1);
    for (int y = 0; y < this->vertices.size(); y++) {
      int y1 = y;
      int y2 = y + 1;
      if (y2 == this->vertices.size())
        y2 = 0;
      math::Vector2D srcVertex1 = this->vertices[i1];
      math::Vector2D srcVertex2 = this->vertices[i2];
      math::Line srcLine(srcVertex1, srcVertex2 - srcVertex1);
    }
  }
  return Polygon(intersections);
}

} // namespace pong::physics
