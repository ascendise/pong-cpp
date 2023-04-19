#include "world.hpp"

namespace pong {
    namespace world {

        Entity::Entity(long id, std::vector<std::shared_ptr<Component>> components) {
            this->id = id;
            this->components = std::vector<std::shared_ptr<Component>>();
            for (auto& component : components) {
                this->components.push_back(std::move(component));
            }
        }

        long Entity::getId() {
            return this->id;
        }

    }
}