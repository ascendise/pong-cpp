#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <memory>
#include <queue>
#include <type_traits>

namespace pong::world::events {

/// @brief Base Event for EventProcessor implementations
/// @n Event is meant to be inherited from to add required data for processing inside the EventProcessor.
class Event {
public:
  virtual ~Event() = default;
};

///  @brief Base EventProessor for implementing event handling
///  @n EventProcessor is meant to be inherited from to handle specific events.
class EventProcessor {
public:
  /// @brief gets an Event (from the EventQueue) and processes it.
  /// @n is responsible for making sure that the Event it is getting is actually the type it expects. In case the event
  /// @n is not meant for this processor, the function should return without making changes.
  /// @n Note: this function may enqueue additional events that later get processed in the same frame.
  virtual void process(const Event &event) = 0;
  virtual ~EventProcessor() = default;
};

/// @brief Write-only interface for EventQueue
/// This interface is exposed by the World when getting the EventQueue. This allows systems to push
/// events without exposing information about queued events.
class IEventQueuePort {
public:
  /// @brief Stores the event for later processing
  virtual void enqueue(std::shared_ptr<Event> &&event) = 0;
  virtual ~IEventQueuePort() = default;
};

/// @brief interface for an EventQueue
/// Exposes interface for pushing generic events, that later get send to the EventProcessors.
/// Event Handling is done inside the EventProcessor, EventQueue is only responsible for storing the events
class IEventQueue : public IEventQueuePort {
public:
  /// @brief Adds an EventProcessor that handles specific events.
  virtual void registerProcessor(std::unique_ptr<EventProcessor> &&processor) = 0;
  /// @brief Processes all queued events for this frame with the registered EventProcessors.
  /// @n Note: EventProcessors may queue additional events that need to be handled in the same frame.
  virtual void processEvents() = 0;
  ~IEventQueue() override = default;
};

/// @brief Simple implementation of EventQueue
class EventQueue : public IEventQueue {
private:
  std::queue<std::shared_ptr<Event>> events;
  std::vector<std::unique_ptr<EventProcessor>> processors;

public:
  EventQueue() = default;
  void registerProcessor(std::unique_ptr<EventProcessor> &&processor) override;
  void enqueue(std::shared_ptr<Event> &&event) override;
  void processEvents() override;
};
} // namespace pong::world::events

#endif
