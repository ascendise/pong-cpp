#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>
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

/// @brief Converts avalue in degrees to radians
float toRadian(float degree);

struct Edge {
private:
  const Vector2D vertex1;
  const Vector2D vertex2;
  float slope() const;
  float slopeIntercept(float slope) const;

public:
  Edge(const Vector2D vertex1, const Vector2D vertex2);
  const Vector2D &getVertex1() const;
  const Vector2D &getVertex2() const;
  Vector2D solvePoint(float x) const;
};

} // namespace pong::math

#endif
