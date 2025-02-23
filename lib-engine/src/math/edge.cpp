#include <math.hpp>

namespace pong::math {

Edge::Edge(Vector2D vertex1, Vector2D vertex2) : vertex1(vertex1), vertex2(vertex2) {}

const Vector2D &Edge::getVertex1() const { return this->vertex1; }
const Vector2D &Edge::getVertex2() const { return this->vertex2; }

Vector2D Edge::solvePoint(float x) const {
  float slope = this->slope();
  float y = slope * x + this->slopeIntercept(slope);
  return Vector2D(x, y);
}

float Edge::slope() const { return (this->vertex2.y - this->vertex1.y) / (this->vertex2.x - this->vertex1.x); }
float Edge::slopeIntercept(float slope) const { return this->vertex1.y - (slope * this->vertex1.x); }

} // namespace pong::math
