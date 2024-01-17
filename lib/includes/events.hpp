#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <type_traits>
#include <queue>
#include <memory>

namespace pong::world::events {

    class Event {
    public:
        virtual ~Event() = default;
    };

    class EventProcessor {
    public:
        virtual void process(Event& event) = 0;
        virtual ~EventProcessor() = default;
    };

    class IEventQueuePort {
    public:
        virtual void enqueue(std::shared_ptr<Event>&& event) = 0;
        virtual ~IEventQueuePort() = default;
    };

    class IEventQueue : public IEventQueuePort {
    public:
        virtual void registerProcessor(std::unique_ptr<EventProcessor>&& processor) = 0;
        virtual void processEvents() = 0;
        ~IEventQueue() override = default;
    };

    class EventQueue : public IEventQueue {
    private:
        std::queue<std::shared_ptr<Event>> events;
        std::vector<std::unique_ptr<EventProcessor>> processors;
    public:
        EventQueue() = default;
        void registerProcessor(std::unique_ptr<EventProcessor>&& processor) override;
        void enqueue(std::shared_ptr<Event>&& event) override;
        void processEvents() override;
    };
}

#endif