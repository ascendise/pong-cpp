#include "world.hpp"

namespace pong {
    namespace world {

        Entity::Entity(Entity&& other) noexcept {
            this->id = other.id;
            this->moveComponents(std::move(other.components));
        }

        void Entity::moveComponents(std::vector<std::unique_ptr<Component>>&& components) {
            this->components.clear();
            for (auto& component : components) {
                this->components.push_back(std::move(component));
            }
        }

        long Entity::getId() const {
            return this->id;
        }

        Entity& Entity::operator=(Entity&& other) noexcept {
            if (this != &other) {
                this->id = other.id;
                this->moveComponents(std::move(other.components));
            }
            return *this;
        }

    }
}