#include <world/events/events.hpp>
#include "fake_event.cpp"

#ifndef FAKE_EVENTPROCESSOR_CPP
#define FAKE_EVENTPROCESSOR_CPP

using pong::world::events::Event;
using pong::world::events::EventProcessor;

class FakeEventProcessor : public EventProcessor {
    public:
        virtual void process(std::shared_ptr<Event> event) {
            auto fakeEvent = std::dynamic_pointer_cast<FakeEvent>(event);
            if(fakeEvent == nullptr) {
                return;
            }
            fakeEvent->process();
        }
};

#endif