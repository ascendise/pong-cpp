#include <chrono>
#include "world.hpp"


namespace pong {
    namespace world {
        
        void Clock::start() {
            timeLastFrame = clock.now();
        }

        void Clock::nextFrame() {
            timeLastFrame = clock.now();
        }

        float Clock::getFrameTimeDelta() {
            auto duration = clock.now() - timeLastFrame;
            auto durationMillis = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
            return durationMillis.count() / 1000.0;
        }

        std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> Clock::now() const {
            return clock.now();
        }

    }
}