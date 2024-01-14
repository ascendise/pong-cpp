#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>
#include <vector>
#include <algorithm>
#include <chrono>
#include <type_traits>
#include <events.hpp>
#include <optional>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::nanoseconds;

namespace pong {
    namespace world {

        class Component { 
        public:
            virtual ~Component() {}
        };

        class Entity {
        private:
            long id;
            std::vector<std::unique_ptr<Component>> components;
            void moveComponents(std::vector<std::unique_ptr<Component>>&& components);
        public:
            Entity(long id, std::vector<std::unique_ptr<Component>>&& components)
                : id(id), components(std::move(components)) {}
            Entity(const Entity&) = delete;
            Entity(Entity&&) noexcept;
            Entity& operator=(const Entity&) = delete;
            Entity& operator=(Entity&&) noexcept;
            long getId() const;
            template<class T>
            std::optional<std::reference_wrapper<T>> getComponent() {
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
            ~Entity() {}
        };

        class System {
        public:
            virtual void run(std::vector<Entity>& entities) = 0;
            virtual ~System() {};
        };

        class IReadOnlyClock {
        public:
            virtual float getFrameTimeDelta() = 0;
            virtual time_point<high_resolution_clock, nanoseconds> now() = 0;
            virtual ~IReadOnlyClock() {};
        };
        
        class Clock : public IReadOnlyClock {
        private:
            high_resolution_clock clock;
            time_point<high_resolution_clock, nanoseconds> timeLastFrame;
        public:
            float getFrameTimeDelta();
            time_point<high_resolution_clock, nanoseconds> now();
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
            IReadOnlyClock& getClock();
            void run();
        };
    }
}

#endif