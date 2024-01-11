#ifndef MATH_HPP
#define MATH_HPP

namespace pong {
	namespace math {

		class Vector2D {
		public:
			float x = 0;
			float y = 0;
			Vector2D(float x, float y);
			Vector2D operator+(const Vector2D& vec) const;
			Vector2D& operator+=(const Vector2D&);
			Vector2D operator-(const Vector2D& vec) const;
			Vector2D& operator-=(const Vector2D& vec);
			Vector2D operator*(float i) const;
			Vector2D& operator*=(float i);
			Vector2D operator/(float i) const;
			Vector2D& operator/=(float i);
			float dot(const Vector2D& v) const;
			float magnitude() const;
			Vector2D normalize() const;
			float angle(const Vector2D& other) const;
		};

		float toDegree(float radian);
		float toRadian(float degree);

	}
}

#endif