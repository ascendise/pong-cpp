#ifndef SPY_EVENTQUEUEPORT
#define SPY_EVENTQUEUEPORT

#include <vector>
#include <world/events/events.hpp>

using namespace pong::world::events;

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