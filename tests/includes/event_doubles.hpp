#ifndef EVENT_DOUBLES_HPP
#define EVENT_DOUBLES_HPP

#include <vector>
#include <events.hpp>

namespace pong::world::events::testing {

	class FakeEvent : public Event {
	private:
	    int base = 0;
	    int* processCount;
	public:
	    FakeEvent() : processCount(&base) { }
	    FakeEvent(int* processCountSpy) : processCount(processCountSpy) { }

			//Events are generally readonly, so we do a little lying here to spy on it
	    void process() const {
	        (*processCount)++;
	    }
	
	    int getProcessCount() const {
	        return *processCount;
	    }
	};
	
	class FakeEventProcessor : public EventProcessor {
	public:
	    void process(const Event& event) override {
	        try {
	            const auto& fakeEvent = dynamic_cast<const FakeEvent&>(event);
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
	    void enqueue(std::shared_ptr<Event>&& event) override {
	        this->events.push_back(std::move(event));
	    }
	
	    std::vector<std::shared_ptr<Event>> const& getEvents() const {
	        return this->events;
	    }
	};
}
#endif
