#ifndef CLOCK_STUB_CPP
#define CLOCK_STUB_CPP

#include <world/world.hpp>

namespace pong {
    namespace world {

        class ClockStub : public IReadOnlyClock {
        private:
            float fixedTimeDelta;
        public:
            ClockStub(float fixedTimeDelta) {
                this->fixedTimeDelta = fixedTimeDelta;
            }
            float getFrameTimeDelta() {
                return fixedTimeDelta;
            };
        };

    }
}

#endif