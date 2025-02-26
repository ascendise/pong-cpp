#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include <math.hpp>
#include <physics.hpp>
#include <vector>

namespace pong::physics {

TEST(PolygonTests, Polygon_CreateWithThreeVertices_ShouldCreatePolygon) {
  // Arrange
  std::vector<math::Vector2D> vertices;
  vertices.push_back(math::Vector2D(-1.0f, 0.0f));
  vertices.push_back(math::Vector2D(1.0f, 0.0f));
  vertices.push_back(math::Vector2D(0.0f, 1.0f));
  // Act
  // Assert
  ASSERT_NO_THROW({ Polygon polygon(vertices); });
}

TEST(PolygonTests, Polygon_CreateWithLessThanThreeVertices_ShouldThrowException) {
  // Arrange
  std::vector<math::Vector2D> vertices;
  vertices.push_back(math::Vector2D(-1.0f, 0.0f));
  vertices.push_back(math::Vector2D(1.0f, 0.0f));
  // Act
  // Assert
  ASSERT_THROW({ Polygon polygon(vertices); }, std::invalid_argument);
}

// TODO: Enable when working on polygons.
//
// To find polygon intersections, one first has to master
// the intersection of lines
//  - Sun Tzu
TEST(PolygonTests, DISABLED_Clip_ClippingPolygons_ShouldReturnClippingSection) {
  // Arrange
  Polygon square1(
      {math::Vector2D(0.0f, 0.0f), math::Vector2D(0.0f, 2.0f), math::Vector2D(2.0f, 2.0f), math::Vector2D(2.0f, 0.0f)});
  Polygon square2(
      {math::Vector2D(1.0f, 1.0f), math::Vector2D(1.0f, 3.0f), math::Vector2D(3.0f, 3.0f), math::Vector2D(3.0f, 1.0f)});
  // Act
  Polygon clip = square1.clip(square2);
  const std::vector<math::Vector2D> &actual = clip.getVertices();
  std::vector<math::Vector2D> expected = {math::Vector2D(1.0f, 2.0f), math::Vector2D(2.0f, 2.0f),
                                          math::Vector2D(2.0f, 1.0f), math::Vector2D(1.0f, 1.0f)};
  ASSERT_THAT(actual, expected);
}

} // namespace pong::physics
