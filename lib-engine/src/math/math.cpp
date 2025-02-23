#include <math.hpp>
#define _USE_MATH_DEFINES // NOLINT; Need to define this to get sweet pi(e)

namespace pong::math {

static const float halfCircleDegrees = 180;

float toDegree(float radian) { return static_cast<float>(radian * math::halfCircleDegrees / M_PI); }

float toRadian(float degree) { return static_cast<float>(degree / math::halfCircleDegrees * M_PI); }
} // namespace pong::math
