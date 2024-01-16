#include "math.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>

namespace pong {
	namespace math {

		static const float halfCircleDegrees = 180;

		Vector2D::Vector2D(float x, float y) : x(x), y(y) { }

		Vector2D Vector2D::operator+(const Vector2D& v) const {
			Vector2D result = *this;
			result.x += v.x;
			result.y += v.y;
			return result;
		}

		Vector2D& Vector2D::operator+=(const Vector2D& v) {
			this->x += v.x;
			this->y += v.y;
			return *this;
		}

		Vector2D Vector2D::operator-(const Vector2D& v) const {
			Vector2D result = *this;
			result.x -= v.x;
			result.y -= v.y;
			return result;
		}

		Vector2D& Vector2D::operator-=(const Vector2D& v) {
			this->x -= v.x;
			this->y -= v.y;
			return *this;
		}

		float Vector2D::dot(const Vector2D& vec) const {
			return this->x * vec.x + this->y * vec.y;
		}

		Vector2D Vector2D::operator*(float i) const {
			Vector2D result = *this;
			result.x *= i;
			result.y *= i;
			return result;
		}

		Vector2D& Vector2D::operator*=(float i) {
			this->x *= i;
			this->y *= i;
			return *this;
		}

		Vector2D Vector2D::operator/(float i) const {
			Vector2D result = *this;
			result.x /= i;
			result.y /= i;
			return result;
		}

		Vector2D& Vector2D::operator/=(float i) {
			this->x /= i;
			this->y /= i;
			return *this;
		}

		float Vector2D::magnitude() const {
			const auto res = std::pow(this->x, 2.0f) + std::pow<float>(this->y, 2.0f);
			return std::sqrt(res);
		}

		Vector2D Vector2D::normalize() const {
			auto magnitude = this->magnitude();
			return Vector2D(
				this->x / magnitude,
				this->y / magnitude
			);
		}

		float Vector2D::angle(const Vector2D& other) const {
			auto angle = this->dot(other) / (this->magnitude() * other.magnitude());
			return toDegree(std::acos(angle));
		}

		float toDegree(float radian) {
			return static_cast<float>(radian * math::halfCircleDegrees / M_PI);
		}

		float toRadian(float degree) {
			return static_cast<float>(degree / math::halfCircleDegrees * M_PI);
		}
	}
}