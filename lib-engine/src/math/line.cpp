#include <math.hpp>

namespace pong::math {

Line::Line(const Vector2D basePoint, const Vector2D direction) : basePoint(basePoint), direction(direction) {}

Vector2D Line::pointAt(float scalar) { return (basePoint + direction) * scalar; }

Vector2D Line::getBasePoint() const { return basePoint; }

Vector2D Line::getDirection() const { return direction; }

} // namespace pong::math
