#include "math.hpp"
#include <gtest/gtest.h>

namespace pong::math {

TEST(Matrix2DTests, IsEqual_Equal_ShouldReturnTrue) {
  // Arrange
  Matrix2D a({1, 2, 3, 4});
  Matrix2D b({1, 2, 3, 4});
  // Act
  bool result = a == b;
  // Assert
  ASSERT_TRUE(result);
}

TEST(Matrix2DTests, IsEqual_NotEqual_ShouldReturnFalse) {
  // Arrange
  Matrix2D a({1, 2, 3, 4});
  Matrix2D b({1, 1, 1, 1});
  // Act
  bool result = a == b;
  // Assert
  ASSERT_FALSE(result);
}

TEST(Matrix2DTests, Multiply_WithScalar_ShoudlReturnNewMatrix) {
  // Arrange
  Matrix2D matrix({1, 2, 3, 4});
  // Act
  Matrix2D result = matrix * 5;
  // Assert
  Matrix2D expected({5, 10, 15, 20});
  ASSERT_EQ(result, expected);
}

TEST(Matrix2DTests, Invert_AnyMatrix_ShouldReturnInvertedMatrix) {
  // Arrange
  Matrix2D matrix({1, 2, 3, 4});
  // Act
  std::optional<Matrix2D> result = matrix.invert();
  // Assert
  Matrix2D expected({-2, 1, 3.0f / 2, -1.0f / 2});
  ASSERT_TRUE(result.has_value()) << "No matrix returned despite it being non-singular!";
  ASSERT_EQ(result.value(), expected);
}

TEST(Matrix2DTests, MultiplyWithVector_Any_ShouldReturnResultAsVector) {
  // Arrange
  // Act
  // Assert
}

} // namespace pong::math
