#include "world.hpp"
#include <chrono>
#include <ratio>

namespace pong::world {

void Clock::start() { timeLastFrame = clock.now(); }

void Clock::nextFrame() {
  auto now = clock.now();
  auto diff = now - timeLastFrame;
  timeLastFrame = now;
  auto timeDiffMillis = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
  auto timeDiffNano = static_cast<float>(timeDiffMillis.count()) / 1000.0f;
  this->timeDiffNano = timeDiffNano;
}

float Clock::getFrameTimeDelta() const { return timeDiffNano; }

std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> Clock::now() const {
  return clock.now();
}
} // namespace pong::world
