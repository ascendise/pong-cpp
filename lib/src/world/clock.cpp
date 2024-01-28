#include "world.hpp"
#include <chrono>

namespace pong::world {

void Clock::start() { timeLastFrame = clock.now(); }

void Clock::nextFrame() { timeLastFrame = clock.now(); }

float Clock::getFrameTimeDelta() const {
  auto duration = clock.now() - timeLastFrame;
  auto durationMillis = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
  return static_cast<float>(durationMillis.count()) / 1000.0f;
}

std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> Clock::now() const {
  return clock.now();
}
} // namespace pong::world