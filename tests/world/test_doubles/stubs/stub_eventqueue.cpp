#ifndef STUB_EVENTQUEUE
#define STUB_EVENTQUEUE

#include <world/world.hpp>
#include <world/events/events.hpp>	

using namespace pong::world::events;

class StubEventQueue : public IEventQueue {
    void registerProcessor(std::unique_ptr<EventProcessor> processor) { }
    void enqueue(std::shared_ptr<Event> event) { }
    void processEvents() { }
};

#endif