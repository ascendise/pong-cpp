#include "test_utility.hpp"
#include <gtest/gtest.h>
#include <math.hpp>

namespace pong::math {

TEST(ToDegreeTests, ToDegree_ShouldReturnValueInDegrees) {
  // Act
  auto result = math::toDegree(1);
  // Assert
  result = test_utility::roundTo(result, 4);
  ASSERT_EQ(result, 57.2958f);
}

TEST(ToRadianTests, ToRadian_ShouldReturnValueInRadians) {
  // Act
  auto result = math::toRadian(69);
  // Assert
  result = test_utility::roundTo(result, 4);
  ASSERT_EQ(result, 1.2043f);
}

TEST(InRangeTests, InRange_IsInRange_ShouldReturnTrue) { ASSERT_TRUE(math::inRange(5, 1, 10)); }

TEST(InRangeTests, InRange_IsInRange_ShouldReturnTrue2) { ASSERT_TRUE(math::inRange(0.25f, 0.0f, 1.0f)); }

TEST(InRangeTests, InRange_NotInRange_ShouldReturnFalse) { ASSERT_FALSE(math::inRange(25, 10, 20)); }

TEST(InRangeTests, InRange_NotInRange_ShouldReturnFalse2) { ASSERT_FALSE(math::inRange(1, -3, -1)); }

} // namespace pong::math
