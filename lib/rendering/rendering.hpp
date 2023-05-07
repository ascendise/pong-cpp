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

        class Sprite : world::Component {
        private:
            SDL_Texture* texture;
            int animationCount;
            int currentAnimation;
            SDL_Rect** animations;
        public:
            Sprite(const std::string& spritePath, int animationCount);
            Sprite(const Sprite&);
            Sprite(const Sprite&&);
            Sprite& operator=(const Sprite&);
            Sprite& operator = (const Sprite&&);
            SDL_Rect* GetNextRect();
        };
    }
}

#endif