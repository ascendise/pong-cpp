#include "test_utility.hpp"

float test_utility::roundTo(float value, int precision) {
	const float multi = std::pow(10, precision);
	return std::round(value * multi) / multi;
}