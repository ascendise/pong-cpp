#include <events.hpp>

#include <memory>
#include <type_traits>

namespace pong::world::events {

void EventQueue::enqueue(std::shared_ptr<Event> &&event) { this->events.push(std::move(event)); }

void EventQueue::registerProcessor(std::unique_ptr<EventProcessor> &&processor) {
  this->processors.push_back(std::move(processor));
}

void EventQueue::processEvents() {
  while (!this->events.empty()) {
    auto &event = events.front();
    for (auto &processor : this->processors) {
      processor->process(*event);
    }
    events.pop();
  }
}
} // namespace pong::world::events