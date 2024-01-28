#include <math.hpp>
#include "test_utility.hpp"
#include <cmath>
#include <gtest/gtest.h>

namespace pong::math {


	TEST(Vector2DTests, AddTwoVectors_PositiveNumbers) {
		//Arrange
		Vector2D const vec1(1, 3);
		Vector2D const vec2(2, 5);
		//Act
		Vector2D const result = vec1 + vec2;
		//Assert
		EXPECT_EQ(result.x, 3);
		EXPECT_EQ(result.y, 8);
	}
	
	TEST(Vector2DTests, AddTwoVectors_NegativeNumbers) {
		//Arrange
		Vector2D const vec1(-1, 5);
		Vector2D const vec2(3, -4);
		//Act
		Vector2D const result = vec1 + vec2;
		//Assert
		EXPECT_EQ(result.x, 2);
		EXPECT_EQ(result.y, 1);
	}
	
	TEST(Vector2DTests, SubtractVectors_PositiveNumbers) {
		//Arrange
		Vector2D const vec1(1, 3);
		Vector2D const vec2(2, 5);
		//Act
		Vector2D const result = vec1 - vec2;
		//Assert
		EXPECT_EQ(result.x, -1);
		EXPECT_EQ(result.y, -2);
	}
	
	TEST(Vector2DTests, SubtractTwoVectors_NegativeNumbers) {
		//Arrange
		Vector2D const vec1(-1, 5);
		Vector2D const vec2(3, -4);
		//Act
		Vector2D const result = vec1 - vec2;
		//Assert
		EXPECT_EQ(result.x, -4);
		EXPECT_EQ(result.y, 9);
	}
	
	TEST(Vector2DTests, MultiplyVector_PositiveNumbers) {
		//Arrange
		Vector2D const vec(2, 3);
		//Act
		Vector2D const result = vec * 3;
		//Assert
		EXPECT_EQ(result.x, 6);
		EXPECT_EQ(result.y, 9);
	}
	
	TEST(Vector2DTests, MultiplyVector_NegativeNumbers) {
		//Arrange
		Vector2D const vec(-2, -5);
		//Act
		Vector2D const result = vec * 3;
		//Assert
		EXPECT_EQ(result.x, -6);
		EXPECT_EQ(result.y, -15);
	}
	
	TEST(Vector2DTests, DotProduct1) {
		//Arrange
		Vector2D const vec1(1, 2);
		Vector2D const vec2(3, 4);
		//Act
		float const result = vec1.dot(vec2);
		//Assert
		EXPECT_EQ(result, 11);
	}
	
	TEST(Vector2DTests, DotProduct12) {
		//Arrange
		Vector2D const vec1(4, -3);
		Vector2D const vec2(1.5, 12);
		//Act
		float const result = vec1.dot(vec2);
		//Assert
		EXPECT_EQ(result, -30);
	}
	
	TEST(Vector2DTests, DotProduct3) {
		//Arrange
		Vector2D const vec1(2, 2);
		Vector2D const vec2(2, 2);
		//Act
		float const result = vec1.dot(vec2);
		//Assert
		EXPECT_EQ(result, 8);
	}
	
	TEST(Vector2DTests, DivideVector_PositiveNumbers) {
		//Arrange
		Vector2D const vec(15, 3);
		//Act
		Vector2D const result = vec / 3;
		//Assert
		EXPECT_EQ(result.x, 5);
		EXPECT_EQ(result.y, 1);
	}
	
	TEST(Vector2DTests, DivideVector_NegativeNumbers) {
		//Arrange
		Vector2D const vec(-6, -12);
		//Act
		Vector2D const result = vec / 3;
		//Assert
		EXPECT_EQ(result.x, -2);
		EXPECT_EQ(result.y, -4);
	}
	
	TEST(Vector2DTests, Magnitude1) {
		//Arrange
		Vector2D const vec(5, 6);
		//Act
		auto result = vec.magnitude();
		//Assert
		auto expectedResult = std::sqrt(61);
		EXPECT_EQ(test_utility::roundTo(result, 4), test_utility::roundTo(expectedResult, 4));
	}
	
	TEST(Vector2DTests, Magnitude2) {
		//Arrange
		Vector2D const vec(-4, 2);
		//Act
		auto result = vec.magnitude();
		//Assert
		auto expectedResult = 2 * std::sqrt(5);
		EXPECT_EQ(test_utility::roundTo(result, 4), test_utility::roundTo(expectedResult, 4));
	}
	
	TEST(Vector2DTests, Magnitude3) {
		//Arrange
		Vector2D const vec(-10, -6);
		//Act
		auto result = vec.magnitude();
		//Assert
		auto expectedResult = 2 * std::sqrt(34);
		EXPECT_EQ(test_utility::roundTo(result, 4), test_utility::roundTo(expectedResult, 4));
	}
	
	TEST(Vector2DTests, Normalize1) {
		//Arrange
		Vector2D const vec(1, 1);
		//Act
		auto newVec = vec.normalize();
		//Assert
		EXPECT_EQ(test_utility::roundTo(newVec.x, 4), 0.7071f);
		EXPECT_EQ(test_utility::roundTo(newVec.y, 4), 0.7071f);
	}
	
	TEST(Vector2DTests, Normalize2) {
		//Arrange
		Vector2D const vec(-5, 2);
		//Act
		auto newVec = vec.normalize();
		//Assert
		EXPECT_EQ(test_utility::roundTo(newVec.x, 4), -0.9285f);
		EXPECT_EQ(test_utility::roundTo(newVec.y, 4), 0.3714f);
	}
	
	TEST(Vector2DTests, Normalize3) {
		//Arrange
		Vector2D const vec(-3, -12);
		//Act
		auto newVec = vec.normalize();
		//Assert
		EXPECT_EQ(test_utility::roundTo(newVec.x, 4), -0.2425f);
		EXPECT_EQ(test_utility::roundTo(newVec.y, 4), -0.9701f);
	}
	
	TEST(Vector2DTests, Angle1) {
		//Arrange
		Vector2D const v(1, 0);
		Vector2D const other(0, 1);
		//Act
		auto result = v.angle(other);
		//Assert
		EXPECT_EQ(result, 90);
	}
	
	TEST(Vector2DTests, Angle2) {
		//Arrange
		Vector2D const v(-1, 0);
		Vector2D const other(1, 0);
		//Act
		auto result = v.angle(other);
		//Assert
		EXPECT_EQ(result, 180);
	}
	
	TEST(Vector2DTests, Angle3) {
		//Arrange
		Vector2D const v(-1, 0);
		Vector2D const other(1, 1);
		//Act
		auto result = v.angle(other);
		//Assert
		EXPECT_EQ(result, 135);
	}
	}
