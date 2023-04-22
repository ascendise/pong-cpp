#include "world.hpp"

#include <stdexcept>

namespace pong {
    namespace world {

        Entity::Entity(long id, std::vector<std::shared_ptr<Component>> components) {
            this->id = id;
            for (auto& component : components) {
                this->components.push_back(std::move(component));
            }
        }

        long Entity::getId() {
            return this->id;
        }

    }
}