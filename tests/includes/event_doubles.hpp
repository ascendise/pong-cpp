#ifndef EVENT_DOUBLES_HPP
#define EVENT_DOUBLES_HPP

#include <vector>
#include <events.hpp>

using namespace pong::world::events;

class FakeEvent : public Event {
private:
    int processCount;
public:
    void process() {
        processCount++;
    }
    bool isProcessed() const {
        return processCount > 0;
    }

    int getProcessCount() const {
        return processCount;
    }
};

class FakeEventProcessor : public EventProcessor {
public:
    virtual void process(std::shared_ptr<Event> event) {
        auto fakeEvent = std::dynamic_pointer_cast<FakeEvent>(event);
        if (fakeEvent == nullptr) {
            return;
        }
        fakeEvent->process();
    }
};

class SpyEventQueuePort : public IEventQueuePort {
private:
    std::shared_ptr<std::vector<std::shared_ptr<Event>>> events;
public:
    SpyEventQueuePort() {
        events = std::make_shared<std::vector<std::shared_ptr<Event>>>(std::vector<std::shared_ptr<Event>>());
    }
    void enqueue(std::shared_ptr<Event> event) {
        this->events->push_back(event);
    }

    std::shared_ptr<std::vector<std::shared_ptr<Event>>> getEvents() {
        return this->events;
    }
};

#endif