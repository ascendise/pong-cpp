#include "rendering.hpp"
#include <stdexcept>
#include <SDL.h>

namespace pong {
    namespace rendering {
        RenderingSystem::RenderingSystem(SDL_Renderer* renderer) {
            this->renderer = renderer;
        }

        void RenderingSystem::run(std::vector<std::shared_ptr<world::Entity>> entities) {
            throw std::runtime_error("Not implemented");
        }
    }
}