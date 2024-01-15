#ifndef RENDERING_HPP
#define RENDERING_HPP

#include <world.hpp>
#include <rendering_utils.hpp>
#include <SDL.h>
#include <string>
#include <stdexcept>

using pong::world::Clock;

namespace pong {
    namespace rendering {
        class RenderingSystem : public world::System { 
        private:
            SDL_Renderer *renderer;
            ScreenPositionCalculator screenCalc;
            const IReadOnlyClock& clock;
            static SDL_Surface* getSurface(SDL_Renderer* renderer);
        public:
            RenderingSystem(SDL_Renderer* renderer, const IReadOnlyClock& clock) :
                renderer(renderer), clock(clock), screenCalc(getSurface(renderer)) {}
            void run(std::vector<Entity>& entities);
        };

        class ITexture {
            public:
            virtual SDL_Texture* getSDLTexture() = 0;
            virtual SDL_Rect getTextureSize() = 0;
        };

        class Texture : public ITexture {
        private:
            SDL_Texture* texture;
            Texture() { texture = nullptr; };
        public:
            static std::unique_ptr<Texture> loadTexture(SDL_Renderer* renderer, std::string path);
            Texture(const Texture&) = delete;
            Texture& operator=(const Texture&) = delete;
            Texture(const Texture&&) noexcept;
            Texture& operator=(const Texture&&) noexcept;
            ~Texture();
            SDL_Texture* getSDLTexture() { return this->texture; }
            SDL_Rect getTextureSize();

        };

        class Sprite : public world::Component {
        private:
            std::unique_ptr<ITexture> texture;
            int spriteCount = 0;
            int currentSprite = 0;
            std::vector<SDL_Rect> sprites;
            std::vector<SDL_Rect> getAnimationRects();
            float avgFrameTime = 0;
            time_point<high_resolution_clock, nanoseconds> lastUpdate;
            bool isPastFrameTime(time_point<high_resolution_clock, nanoseconds> time);
        public:
            Sprite(std::unique_ptr<ITexture>&& texture, int spriteCount, float duration);
            const SDL_Rect getNextRect(time_point<high_resolution_clock, nanoseconds> currentTime);
            std::unique_ptr<ITexture>& getTexture();
        };
    }
}

#endif