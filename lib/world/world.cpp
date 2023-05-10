#include "world.hpp"

#include <stdexcept>
#include <algorithm>

namespace pong {
    namespace world {

        std::shared_ptr<Entity> World::registerEntity(std::vector<std::shared_ptr<Component>> components) {
            auto entity = std::make_shared<Entity>(Entity(this->idCounter++, components));
            this->entities.push_back(std::shared_ptr<Entity>(entity));
            return std::shared_ptr<Entity>(entity);
        }

        void World::removeEntity(long entityId) {
            auto has_id = [entityId](std::shared_ptr<Entity> e) { return e->getId() == entityId; };
            auto remove_if_has_id = std::remove_if(this->entities.begin(), this->entities.end(), has_id);
            this->entities.erase(remove_if_has_id, this->entities.end());
        }

        void World::registerSystem(std::unique_ptr<System> system) {
            this->systems.push_back(std::move(system));
        }

        void World::run() {
            for (auto& system : this->systems) {
                system->run(this->entities);
            }
        }
    }
}