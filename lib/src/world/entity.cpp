#include <world.hpp>

#include <memory>
#include <type_traits>
#include <vector>

namespace pong::world {

Entity::Entity(Entity &&other) noexcept : id(other.id) { this->moveComponents(std::move(other.components)); }

void Entity::moveComponents(std::vector<std::unique_ptr<Component>> &&components) noexcept {
  this->components.clear();
  for (auto &component : components) {
    try {
      this->components.push_back(std::move(component));
    } catch (std::exception &e) {
      // Now Idea what to do here, but I need this to be noexcept
    }
  }
}

long Entity::getId() const noexcept { return this->id; }

Entity &Entity::operator=(Entity &&other) noexcept {
  if (this != &other) {
    this->id = other.id;
    this->moveComponents(std::move(other.components));
  }
  return *this;
}
} // namespace pong::world