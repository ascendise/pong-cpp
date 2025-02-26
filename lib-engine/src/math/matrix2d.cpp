#include <math.hpp>

namespace pong::math {

Matrix2D::Matrix2D(std::array<std::array<float, 2>, 2> data) : data(data) {}

Vector2D Matrix2D::operator*(const Vector2D &vector) const { return Vector2D(0, 0); }

Matrix2D Matrix2D::invert() const { return *this; }

} // namespace pong::math
