#include <world.hpp>

#include <memory>
#include <type_traits>
#include <vector>

namespace pong::world {

long Entity::getId() const noexcept { return this->id; }

} // namespace pong::world