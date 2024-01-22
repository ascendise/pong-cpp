#include <math.hpp>
#include "test_utility.hpp"
#include <gtest/gtest.h>

namespace pong::math {

	TEST(RadianDegreeTests, ToDegree_ShouldReturnValueInDegrees) {
		//Act
		auto result = math::toDegree(1);
		//Assert
		result = test_utility::roundTo(result, 4);
		EXPECT_EQ(result, 57.2958f);
	}
	
	TEST(RadianDegreeTests, ToRadian_ShouldReturnValueInRadians) {
		//Act
		auto result = math::toRadian(69);
		//Asssert
		result = test_utility::roundTo(result, 4);
		EXPECT_EQ(result, 1.2043f);
	}
}
