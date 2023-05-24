#include <chrono>
#include "world.hpp"

using std::chrono::milliseconds;

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
            auto durationMillis = std::chrono::duration_cast<milliseconds>(duration);
            return durationMillis.count() / 1000.0;
        }

    }
}