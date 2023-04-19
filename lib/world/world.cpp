#include "world.hpp"

#include <stdexcept>

namespace pong {
    namespace world {

        std::shared_ptr<Entity> World::registerEntity(std::vector<std::shared_ptr<Component>> components) {
            auto entity = std::make_shared<Entity>(Entity(this->idCounter++, components));
            this->entities = std::vector<std::shared_ptr<Entity>>();
            this->entities.push_back(std::shared_ptr<Entity>(entity));
            return std::shared_ptr<Entity>(entity);
        }
    }
}