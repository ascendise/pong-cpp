#ifndef RENDERING_HPP
#define RENDERING_HPP

#include "../world/world.hpp"
#include <SDL.h>
#include <string>

namespace pong {
    namespace rendering {
        class RenderingSystem : world::System { 
        private:
            SDL_Renderer *renderer;
        public:
            RenderingSystem(SDL_Renderer *renderer);
            void run(std::vector<std::shared_ptr<world::Entity>> entities);
        };

        class Texture {
        private:
            SDL_Texture* texture;
            Texture() = default;
        public:
            static Texture& LoadTexture(SDL_Renderer* renderer, std::string path);
            Texture(const Texture&) = delete;
            Texture(const Texture&& other) { this->texture = texture; }
            Texture& operator=(const Texture&) = delete;
            Texture& operator=(const Texture&& other) noexcept {
                if (this != &other) {
                    this->texture = other.texture;
                }
                return *this;
            }
            ~Texture() {
                SDL_DestroyTexture(this->texture);
            };

        };

        class Sprite : world::Component {
        private:
            std::shared_ptr<Texture> texture;
            int spriteCount;
            int currentAnimation;
            const SDL_Rect** animations;
        public:
            Sprite(std::shared_ptr<Texture> texture, int spriteCount);
            const SDL_Rect* GetNextRect();
            std::shared_ptr<Texture> GetTexture();
        };
    }
}

#endif