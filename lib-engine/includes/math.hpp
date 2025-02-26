#ifndef MATH_HPP
#define MATH_HPP

#include <array>
#include <cmath>
#include <optional>
#include <ostream>

namespace pong::math {

/// @brief implementation of a vector with two elements
/// @n used for calculations in 2D Space
/// @n Includes (partial) support for vector arithmetic
class Vector2D {

  friend void PrintTo(const Vector2D &vec, std::ostream *os) { *os << "(x: " << vec.x << ", y: " << vec.y << ")"; }

public:
  float x = 0; // NOLINT misc-non-private-member-variables-in-classes; This
               // class is designed to use public members
  float y = 0; // NOLINT misc-non-private-member-variables-in-classes; This
               // class is designed to use public members
  Vector2D(float x, float y);
  Vector2D operator+(const Vector2D &vec) const;
  Vector2D &operator+=(const Vector2D &);
  Vector2D operator-(const Vector2D &vec) const;
  Vector2D &operator-=(const Vector2D &vec);
  Vector2D operator*(float i) const;
  Vector2D &operator*=(float i);
  Vector2D operator/(float i) const;
  Vector2D &operator/=(float i);
  bool operator==(const Vector2D &vec) const;
  float dot(const Vector2D &v) const;
  float magnitude() const;
  Vector2D normalize() const;
  float angle(const Vector2D &other) const;
};

/// @brief Converts a value in radians to degrees
float toDegree(float radian);

/// @brief Converts a value in degrees to radians
float toRadian(float degree);

/// @brief implementation of a 2x2 matrix
/// @n used for calculations in 2D Space
/// @n Includes (partial) support for matrix arithmetic
class Matrix2D {

  friend void PrintTo(const Matrix2D &matrix, std::ostream *os) {
    *os << "\n"
        << "[" << matrix.data[0][0] << ", " << matrix.data[0][1] << "],\n"
        << "[" << matrix.data[1][0] << ", " << matrix.data[1][1] << "]";
  }

public:
  std::array<std::array<float, 2>, 2> data; // NOLINT misc-non-private-member-variables-in-classes; This
                                            // class is designed to use public members

  Matrix2D(std::array<std::array<float, 2>, 2> data);
  Matrix2D operator*(float scalar) const;
  Vector2D operator*(const Vector2D &vector) const;
  bool operator==(const Matrix2D &other) const;
  /// @brief returns the inverted matrix or nothing if the matrix is singular
  std::optional<Matrix2D> invert() const;
};

class Line {
private:
  const Vector2D basePoint;
  const Vector2D direction;

public:
  Line(const Vector2D basePoint, const Vector2D direction);
  Vector2D getBasePoint() const;
  Vector2D getDirection() const;
  /// @brief calculates a point on the line given the scalar parameter
  Vector2D getPointAt(float scalar) const;
  std::optional<Vector2D> findIntersect(const Line &other) const;
};

} // namespace pong::math

#endif
