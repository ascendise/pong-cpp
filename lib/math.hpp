#ifndef MATH_HPP
#define MATH_HPP

namespace pong {
	namespace math {

		class Vector2D {
		public:
			float x = 0;
			float y = 0;
			Vector2D(float x, float y);
			Vector2D operator+(Vector2D vec);
			Vector2D& operator+=(Vector2D);
			Vector2D operator-(Vector2D vec);
			Vector2D& operator-=(Vector2D vec);
			Vector2D operator*(float i);
			Vector2D& operator*=(float i);
			Vector2D operator/(float i);
			Vector2D& operator/=(float i);
		};

	}
}

#endif