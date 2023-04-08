#include "world.hpp"

#include <stdexcept>

namespace pong {
    namespace world {

        Entity& World::registerEntity(std::unique_ptr<Component> components[]) {
            throw std::runtime_error("Not implemented");
        }
    }
}