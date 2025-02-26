#include <math.hpp>
#include <optional>

namespace pong::math {

Line::Line(const Vector2D basePoint, const Vector2D direction) : basePoint(basePoint), direction(direction) {}

Vector2D Line::getBasePoint() const { return basePoint; }

Vector2D Line::getDirection() const { return direction; }

Vector2D Line::getPointAt(float scalar) const { return (basePoint + direction) * scalar; }

std::optional<Vector2D> Line::findIntersect(const Line &other) const {
  int a = 0;
  return {};
}

} // namespace pong::math
