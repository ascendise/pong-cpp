#include <gtest/gtest.h>
#include <math.hpp>

namespace pong::math {

TEST(LineTests, FindIntersect_Intersects_ShouldReturnIntersectionPoint) {
  // Arrange
  Line horizontal(Vector2D(-1, 2), Vector2D(3, 0));
  Line vertical(Vector2D(0, 0), Vector2D(0, 3));
  // Act
  std::optional<Vector2D> intersect = horizontal.findIntersect(vertical);
  // Assert
  ASSERT_TRUE(intersect.has_value());
  Vector2D expected(0, 2);
  ASSERT_EQ(intersect, expected);
}

TEST(LineTests, FindIntersect_DiagonalIntersects_ShouldReturnIntersectionPoint) {
  // Arrange
  Line line1(Vector2D(0, 0), Vector2D(2, 2));
  Line line2(Vector2D(2, 0), Vector2D(-2, 2));
  // Act
  std::optional<Vector2D> intersect = line1.findIntersect(line2);
  // Assert
  ASSERT_TRUE(intersect.has_value());
  Vector2D expected(1, 1);
  ASSERT_EQ(intersect, expected);
}

TEST(LineTests, FindIntersect_Parallel_ShouldReturnNothing) {
  // Arrange
  Line vertical(Vector2D(0, 0), Vector2D(0, 3));
  Line vertical2(Vector2D(1, 0), Vector2D(0, 3));
  // Act
  std::optional<Vector2D> intersect = vertical.findIntersect(vertical2);
  // Assert
  ASSERT_FALSE(intersect.has_value());
}

TEST(LineTests, FindIntersect_InEachother_ShouldReturnNothing) {
  // Arrange
  Line horizontal1(Vector2D(0, 0), Vector2D(3, 0));
  Line horizontal2(Vector2D(1, 0), Vector2D(3, 0));
  // Act
  std::optional<Vector2D> intersect = horizontal1.findIntersect(horizontal2);
  // Assert
  ASSERT_FALSE(intersect.has_value());
}

TEST(LineTests, FindIntersect_NoIntersect_ShouldReturnNothing) {
  // Arrange
  Line line1(Vector2D(0, 0), Vector2D(3, 0));
  Line line2(Vector2D(2, 3), Vector2D(0, 1));
  // Act
  std::optional<Vector2D> intersect = line1.findIntersect(line2);
  // Assert
  ASSERT_FALSE(intersect.has_value());
}

TEST(LineTests, FindIntersect_NoIntersect_ShouldReturnNothing2) {
  // Arrange
  Line line1(Vector2D(1, 3), Vector2D(2, 0));
  Line line2(Vector2D(3, 0), Vector2D(0, 2));
  // Act
  std::optional<Vector2D> intersect = line1.findIntersect(line2);
  // Assert
  ASSERT_FALSE(intersect.has_value());
}

} // namespace pong::math
