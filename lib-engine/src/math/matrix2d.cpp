#include <math.hpp>

namespace pong::math {

Matrix2D::Matrix2D(std::array<std::array<float, 2>, 2> data) : data(data) {}

Matrix2D Matrix2D::operator*(float scalar) const {
  return Matrix2D({data[0][0] * scalar, data[0][1] * scalar, data[1][0] * scalar, data[1][1] * scalar});
}

Vector2D Matrix2D::operator*(const Vector2D &vector) const {
  return Vector2D((data[0][0] * vector.x) + (data[0][1] * vector.y), (data[1][0] * vector.x) + (data[1][1] * vector.y));
}

bool Matrix2D::operator==(const Matrix2D &other) const { return this->data == other.data; }

std::optional<Matrix2D> Matrix2D::invert() const {
  float determinant = data[0][0] * data[1][1] - data[0][1] * data[1][0];
  if (determinant == 0)
    return {};
  Matrix2D inverse({data[1][1], -1 * data[0][1], -1 * data[1][0], data[0][0]});
  return inverse * (1 / determinant);
}

} // namespace pong::math
