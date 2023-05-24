#include <math.hpp>
#include <gtest/gtest.h>

using pong::math::Vector2D;

TEST(Vector2DTests, AddTwoVectors_PositiveNumbers) {
	//Arrange
	Vector2D vec1(1, 3);
	Vector2D vec2(2, 5);
	//Act
	Vector2D result = vec1 + vec2;
	//Assert
	EXPECT_EQ(result.x, 3);
	EXPECT_EQ(result.y, 8);
}

TEST(Vector2DTests, AddTwoVectors_NegativeNumbers) {
	//Arrange
	Vector2D vec1(-1, 5);
	Vector2D vec2(3, -4);
	//Act
	Vector2D result = vec1 + vec2;
	//Assert
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 1);
}

TEST(Vector2DTests, SubtractVectors_PositiveNumbers) {
	//Arrange
	Vector2D vec1(1, 3);
	Vector2D vec2(2, 5);
	//Act
	Vector2D result = vec1 - vec2;
	//Assert
	EXPECT_EQ(result.x, -1);
	EXPECT_EQ(result.y, -2);
}

TEST(Vector2DTests, SubtractTwoVectors_NegativeNumbers) {
	//Arrange
	Vector2D vec1(-1, 5);
	Vector2D vec2(3, -4);
	//Act
	Vector2D result = vec1 - vec2;
	//Assert
	EXPECT_EQ(result.x, -4);
	EXPECT_EQ(result.y, 9);
}

TEST(Vector2DTests, MultiplyVector_PositiveNumbers) {
	//Arrange
	Vector2D vec(2, 3);
	//Act
	Vector2D result = vec * 3;
	//Assert
	EXPECT_EQ(result.x, 6);
	EXPECT_EQ(result.y, 9);
}

TEST(Vector2DTests, MultiplyVector_NegativeNumbers) {
	//Arrange
	Vector2D vec(-2, -5);
	//Act
	Vector2D result = vec * 3;
	//Assert
	EXPECT_EQ(result.x, -6);
	EXPECT_EQ(result.y, -15);
}

TEST(Vector2DTests, DivideVector_PositiveNumbers) {
	//Arrange
	Vector2D vec(15, 3);
	//Act
	Vector2D result = vec / 3;
	//Assert
	EXPECT_EQ(result.x, 5);
	EXPECT_EQ(result.y, 1);
}

TEST(Vector2DTests, DivideVector_NegativeNumbers) {
	//Arrange
	Vector2D vec(-6, -12);
	//Act
	Vector2D result = vec / 3;
	//Assert
	EXPECT_EQ(result.x, -2);
	EXPECT_EQ(result.y, -4);
}