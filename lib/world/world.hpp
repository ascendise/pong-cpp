#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>
#include <vector>
#include <algorithm>

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

        class World {
        private:
            long idCounter = 0;
            std::vector<std::shared_ptr<Entity>> entities;
            std::vector<std::unique_ptr<System>> systems;
        public: 
            std::shared_ptr<Entity> registerEntity(std::vector<std::shared_ptr<Component>> components);
            void removeEntity(long entityId);
            void registerSystem(std::unique_ptr<System> system);
            void run();
        };

    }
}

#endif