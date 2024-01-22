#include <test_utility.hpp>
#include <cmath>

float test_utility::roundTo(float value, int precision) {
  const auto multi = static_cast<float>(std::pow(10, precision));
  return std::round(value * multi) / multi;
}
