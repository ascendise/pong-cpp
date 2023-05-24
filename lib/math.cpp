#include "math.hpp"

using pong::math::Vector2D;

Vector2D::Vector2D(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2D Vector2D::operator+(Vector2D v) {
	Vector2D result = *this;
	result.x += v.x;
	result.y += v.y;
	return result;
}

Vector2D& Vector2D::operator+=(Vector2D v) {
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vector2D Vector2D::operator-(Vector2D v) {
	Vector2D result = *this;
	result.x -= v.x;
	result.y -= v.y;
	return result;
}

Vector2D& Vector2D::operator-=(Vector2D v) {
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

Vector2D Vector2D::operator*(float i) {
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

Vector2D Vector2D::operator/(float i) {
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