#include <physics.hpp>

namespace pong::physics {

Polygon::Polygon(std::vector<math::Vector2D> vertices) : vertices(vertices) {
	if(vertices.size() < 3)
		throw std::invalid_argument("requires at least 3 vertices");
}

const std::vector<math::Vector2D>& Polygon::getVertices() const {
	return this->vertices;	
}

Polygon Polygon::clip(const Polygon& clippingPolygon) const {
	return Polygon(std::vector<math::Vector2D>());
}


}