#ifndef RENDERING_HPP
#define RENDERING_HPP

#include "../world/world.hpp"
#include <SDL.h>
#include <string>
#include <stdexcept>

namespace pong {
    namespace rendering {
        class RenderingSystem : public world::System { 
        private:
            SDL_Renderer *renderer;
        public:
            RenderingSystem(SDL_Renderer *renderer);
            void run(std::vector<std::shared_ptr<pong::world::Entity>> entities);
        };

        class Texture {
        private:
            SDL_Texture* texture;
            Texture() { };
        public:
            static std::shared_ptr<Texture> loadTexture(SDL_Renderer* renderer, std::string path);
            Texture(const Texture&) = delete;
            Texture& operator=(const Texture&) = delete;
            Texture(const Texture&&) noexcept;
            Texture& operator=(const Texture&&) noexcept;
            ~Texture();
            SDL_Texture* getSDLTexture() { return this->texture; }

        };

        class Sprite : public world::Component {
        private:
            std::shared_ptr<Texture> texture;
            int spriteCount;
            int currentSprite;
            std::vector<SDL_Rect> sprites;
            std::vector<SDL_Rect> getAnimationRects();
            SDL_Rect getTextureSize();
        public:
            Sprite(std::shared_ptr<Texture> texture, int spriteCount);
            const SDL_Rect getNextRect();
            std::shared_ptr<Texture> getTexture();
        };
    }
}

#endif