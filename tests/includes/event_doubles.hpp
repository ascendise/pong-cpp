#ifndef EVENT_DOUBLES_HPP
#define EVENT_DOUBLES_HPP

#include <vector>
#include <events.hpp>

using namespace pong::world::events;

class FakeEvent : public Event {
private:
    int* processCount;
public:

    void process() {
        *processCount++;
    }

    int getProcessCount() const {
        return *processCount;
    }

    int* spyOnProcessCount() const {
        return processCount;
    }
};

class FakeEventProcessor : public EventProcessor {
public:
    virtual void process(Event& event) {
        try {
            auto& fakeEvent = dynamic_cast<FakeEvent&>(event);
            fakeEvent.process();
        }
        catch (std::bad_cast&) {
            //Not my event, return
            return;
        }
    }
};

class SpyEventQueuePort : public IEventQueuePort {
private:
    std::vector<Event> events;
public:
    void enqueue(Event&& event) {
        this->events.push_back(event);
    }

    std::vector<Event> const& getEvents() const {
        return this->events;
    }
};

#endif