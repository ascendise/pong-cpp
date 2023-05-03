#ifndef RENDERING_HPP
#define RENDERING_HPP

#include "../world/world.hpp"
#include <SDL.h>

namespace pong {
    namespace rendering {
        class RenderingSystem : world::System { 
        private:
            SDL_Renderer *renderer;
        public:
            RenderingSystem(SDL_Renderer *renderer);
            void run(std::vector<std::shared_ptr<world::Entity>> entities);
        }; 

    }
}

#endif