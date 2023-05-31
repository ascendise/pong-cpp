#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>
#include <vector>
#include <algorithm>
#include <chrono>

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
            std::vector<std::shared_ptr<Component>> components;
        public:
            Entity(long id, std::vector<std::shared_ptr<Component>> components);
            long getId();
            template<class T>
            std::shared_ptr<T> getComponent() {
                for (auto& componentPtr : this->components) {
                    auto derived = std::dynamic_pointer_cast<T>(componentPtr);
                    if (derived != nullptr) {
                        return std::shared_ptr<T>(derived);
                    }
                }
                return std::shared_ptr<T>(nullptr);
            }
        };

        class System {
        public:
            virtual void run(std::vector<std::shared_ptr<Entity>> entities) = 0;
        };

        class IReadOnlyClock {
        public:
            virtual float getFrameTimeDelta() = 0;
            virtual time_point<high_resolution_clock, nanoseconds> now() = 0;
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
            std::vector<std::shared_ptr<Entity>> entities;
            std::vector<std::unique_ptr<System>> systems;
            std::shared_ptr<Clock> clock;
        public: 
            World();
            std::shared_ptr<Entity> registerEntity(std::vector<std::shared_ptr<Component>> components);
            void removeEntity(long entityId);
            void registerSystem(std::unique_ptr<System> system);
            std::shared_ptr<IReadOnlyClock> getClock();
            void run();
        };

    }
}

#endif