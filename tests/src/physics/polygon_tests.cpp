#include <gtest/gtest.h>
#include <math.hpp>
#include <physics.hpp>

namespace pong::physics {

TEST(PolygonTests, Polygon_CreateWithThreeVertices_ShouldCreatePolygon) {
	// Arrange
	std::vector<math::Vector2D> vertices;
	vertices.push_back(math::Vector2D(-1, 0));
	vertices.push_back(math::Vector2D(1, 0));
	vertices.push_back(math::Vector2D(0, 1));
	// Act
	// Assert
	ASSERT_NO_THROW({
		Polygon polygon(vertices);	
	});
}

TEST(PolygonTests, Polygon_CreateWithLessThanThreeVertices_ShouldThrowException) {
	// Arrange
	std::vector<math::Vector2D> vertices;
	vertices.push_back(math::Vector2D(-1, 0));
	vertices.push_back(math::Vector2D(1, 0));
	// Act
	// Assert
	ASSERT_THROW({
		Polygon polygon(vertices);	
	}, std::invalid_argument);
}

}