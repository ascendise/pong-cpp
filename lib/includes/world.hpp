#ifndef WORLD_HPP
#define WORLD_HPP

#include <events.hpp>

#include <memory>
#include <vector>
#include <algorithm>
#include <chrono>
#include <type_traits>
#include <optional>


namespace pong::world {

    class Component { 
    public: 
        virtual ~Component() = default;
    };

    class Entity {
    private:
        long id;
        std::vector<std::unique_ptr<Component>> components;
        void moveComponents(std::vector<std::unique_ptr<Component>>&& components) noexcept;
    public:
        Entity(long id, std::vector<std::unique_ptr<Component>>&& components)
            : id(id), components(std::move(components)) {}
        Entity(const Entity&) = delete;
        Entity(Entity&&) noexcept;
        Entity& operator=(const Entity&) = delete;
        Entity& operator=(Entity&&) noexcept;
        long getId() const noexcept;
        template<class T>
        std::optional<std::reference_wrapper<T>> getComponent() const {
            for (const auto& component: this->components) {
                try {
                    auto& derived = dynamic_cast<T&>(*component);
                    return std::ref(derived);
                }
                catch (std::bad_cast&) {
                    //Try next component
                }
            }
            return {};
        }
        ~Entity() = default;
    };

    class System {
    public:
        virtual void run(std::vector<Entity>& entities) = 0;
        virtual ~System() = default;
    };

    class IReadOnlyClock {
    public:
        virtual float getFrameTimeDelta() const = 0;
        virtual std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> now() const = 0;
        virtual ~IReadOnlyClock() = default;
    };
        
    class Clock : public IReadOnlyClock {
    private:
        std::chrono::high_resolution_clock clock;
        std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> timeLastFrame;
    public:
        float getFrameTimeDelta() const override;
        std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> now() const override;
        void start();
        void nextFrame();
    };

    class World {
    private:
        long idCounter = 0;
        std::vector<Entity> entities;
        std::vector<std::unique_ptr<System>> systems;
        std::unique_ptr<events::IEventQueue> eventQueue;
        std::unique_ptr<Clock> clock;
    public: 
        World(std::unique_ptr<events::IEventQueue>&& eventQueue);
        void registerEntity(std::vector<std::unique_ptr<Component>>&& components);
        void removeEntity(long entityId);
        std::optional<std::reference_wrapper<Entity>> findEntity(long entityId);
        void registerSystem(std::unique_ptr<System>&& system);
        events::IEventQueuePort& getEventQueue();
        IReadOnlyClock& getClock() const;
        void run();
    };
}

#endif