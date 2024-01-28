#include <cmath>
#include <test_utility.hpp>

float test_utility::roundTo(float value, int precision) {
  const auto multi = static_cast<float>(std::pow(10, precision));
  return std::round(value * multi) / multi;
}
