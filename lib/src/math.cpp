#include "math.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>

namespace pong {
	namespace math {

		Vector2D::Vector2D(float x, float y) {
			this->x = x;
			this->y = y;
		}

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
			const auto res = std::pow(this->x, 2) + std::pow(this->y, 2);
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
			return radian * 180 / M_PI;
		}

		float toRadian(float degree) {
			return degree / 180 * M_PI;
		}
	}
}