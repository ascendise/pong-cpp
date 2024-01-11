#ifndef FAKE_EVENT_CPP
#define FAKE_EVENT_CPP

#include <world/events/events.hpp>

class FakeEvent :  public pong::world::events::Event {
    private:
        int processCount;
    public:
        void process() {
            processCount++;
        }
        bool isProcessed() {
            return processCount > 0;
        }

        int getProcessCount() {
            return processCount;
        }
};

#endif