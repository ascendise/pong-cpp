#ifndef MATH_HPP
#define MATH_HPP

namespace pong::math {

/// @brief implementation of a vector with two elements
/// @n used for calculations in 2D Space
/// @n Includes (partial) support for vector arithmetic
class Vector2D {
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
  float dot(const Vector2D &v) const;
  float magnitude() const;
  Vector2D normalize() const;
  float angle(const Vector2D &other) const;
};

/// @brief Converts a value in radians to degrees
float toDegree(float radian);

/// @brief Converts avalue in degrees to radians
float toRadian(float degree);

} // namespace pong::math

#endif
