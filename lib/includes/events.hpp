#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <type_traits>
#include <queue>
#include <memory>

namespace pong::world::events {

    class Event {
    public:
        virtual ~Event() {}
    };

    class EventProcessor {
    public:
        virtual void process(Event& event) = 0;
        virtual ~EventProcessor() {}
    };

    class IEventQueuePort {
    public:
        virtual void enqueue(std::shared_ptr<Event>&& event) = 0;
    };

    class IEventQueue : public IEventQueuePort {
    public:
        virtual void registerProcessor(std::unique_ptr<EventProcessor>&& processor) = 0;
        virtual void processEvents() = 0;
        virtual ~IEventQueue() {}
    };

    class EventQueue : public IEventQueue {
    private:
        std::queue<std::shared_ptr<Event>> events;
        std::vector<std::unique_ptr<EventProcessor>> processors;
    public:
        EventQueue() {}
        void registerProcessor(std::unique_ptr<EventProcessor>&& processor);
        void enqueue(std::shared_ptr<Event>&& event);
        void processEvents();
    };
}

#endif