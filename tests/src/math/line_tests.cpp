#include <gtest/gtest.h>
#include <math.hpp>

namespace pong::math {

TEST(LineTests, FindIntersect_Intersects_ShouldReturnIntersectionPoint) {
  // Arrange
  Line vertical(Vector2D(0, 0), Vector2D(0, 3));
  Line horizontal(Vector2D(-1, 2), Vector2D(3, 0));
  // Act
  std::optional<Vector2D> intersect = vertical.findIntersect(horizontal);
  // Assert
  ASSERT_TRUE(intersect.has_value());
  Vector2D expected(0, 2);
  ASSERT_EQ(intersect, expected);
}

TEST(Matrix2DTests, FindIntersect_Parallel_ShouldReturnNothing) {
  // Arrange
  Line vertical(Vector2D(0, 0), Vector2D(0, 3));
  Line vertical2(Vector2D(1, 0), Vector2D(0, 3));
  // Act
  std::optional<Vector2D> intersect = vertical.findIntersect(vertical2);
  // Assert
  ASSERT_FALSE(intersect.has_value());
}

TEST(Matrix2DTests, FindIntersect_InEachother_ShouldReturnNothing) {
  // Arrange
  Line horizontal1(Vector2D(0, 0), Vector2D(3, 0));
  Line horizontal2(Vector2D(1, 0), Vector2D(3, 0));
  // Act
  std::optional<Vector2D> intersect = horizontal1.findIntersect(horizontal2);
  // Assert
  ASSERT_FALSE(intersect.has_value());
}

} // namespace pong::math
