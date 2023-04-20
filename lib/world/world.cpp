#include "world.hpp"

#include <stdexcept>

namespace pong {
    namespace world {

        std::shared_ptr<Entity> World::registerEntity(std::vector<std::shared_ptr<Component>> components) {
            auto entity = std::make_shared<Entity>(Entity(this->idCounter++, components));
            this->entities.push_back(std::shared_ptr<Entity>(entity));
            return std::shared_ptr<Entity>(entity);
        }

        void World::registerSystem(std::unique_ptr<System> system) {
            this->systems.push_back(std::move(system));
        }

        void World::run() {
            for (auto& system : this->systems) {
                system.get()->run(this->entities);
            }
        }
    }
}