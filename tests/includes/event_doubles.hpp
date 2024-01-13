#ifndef EVENT_DOUBLES_HPP
#define EVENT_DOUBLES_HPP

#include <vector>
#include <events.hpp>

using namespace pong::world::events;

class FakeEvent : public Event {
private:
    int base = 0;
    int* processCount;
public:
    FakeEvent(): processCount(&base) { }
    FakeEvent(int* processCountSpy): processCount(processCountSpy) { }

    void process() {
        (*processCount)++;
    }

    int getProcessCount() const {
        return *processCount;
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
    std::vector<std::shared_ptr<Event>> events;
public:
    void enqueue(std::shared_ptr<Event>&& event) {
        this->events.push_back(std::move(event));
    }

    std::vector<std::shared_ptr<Event>> const& getEvents() const {
        return this->events;
    }
};

#endif