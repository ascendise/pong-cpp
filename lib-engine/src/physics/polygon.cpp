#include <physics.hpp>

namespace pong::physics {

Polygon::Polygon(std::vector<math::Vector2D> vertices) : vertices(vertices) {

}

const std::vector<math::Vector2D>& Polygon::getVertices() const {
	return this->vertices;	
}

Polygon Polygon::clip(const Polygon& clippingPolygon) const {
}


}