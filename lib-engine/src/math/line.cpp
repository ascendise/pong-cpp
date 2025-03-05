#include <math.hpp>
#include <optional>

namespace pong::math {

Line::Line(const Vector2D basePoint, const Vector2D direction) : basePoint(basePoint), direction(direction) {}

Vector2D Line::getBasePoint() const { return basePoint; }

Vector2D Line::getDirection() const { return direction; }

Vector2D Line::getPointAt(float scalar) const { return basePoint + (direction * scalar); }

std::optional<Vector2D> Line::findIntersect(const Line &other) const {
  auto scalars = Line::findIntersectPointArgs(other);
  if (!scalars.has_value())
    return {};
  if (!math::inRange((*scalars).x, 0.0f, 1.0f) || !math::inRange((*scalars).y, 0.0f, 1.0f))
    return {};
  return this->getPointAt((*scalars).x);
}

std::optional<Vector2D> Line::findIntersectPointArgs(const Line &other) const {
  Matrix2D directions(
      {this->getDirection().x, -1 * other.getDirection().x, this->getDirection().y, -1 * other.getDirection().y});
  auto invert = directions.invert();
  if (!invert.has_value())
    return {};
  Vector2D difference = other.getBasePoint() - this->getBasePoint();
  Vector2D scalars = *invert * difference;
  return scalars;
}

std::optional<Vector2D> Line::findIntersectInfinite(const Line &other) const {
  auto scalars = Line::findIntersectPointArgs(other);
  if (!scalars.has_value())
    return {};
  return this->getPointAt((*scalars).x);
}

} // namespace pong::math
