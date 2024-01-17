#ifndef RENDERING_HPP
#define RENDERING_HPP

#include <world.hpp>
#include <rendering_utils.hpp>

#include <SDL.h>
#include <string>
#include <stdexcept>

namespace pong::rendering {

    class RenderingSystem : public world::System { 
    private:
        SDL_Renderer *renderer;
        ScreenPositionCalculator screenCalc;
        world::IReadOnlyClock& clock;
        static SDL_Surface* getSurface(SDL_Renderer* renderer);
    public:
        RenderingSystem(SDL_Renderer* renderer, world::IReadOnlyClock& clock) :
            renderer(renderer), clock(clock), screenCalc(getSurface(renderer)) { }
        void run(std::vector<world::Entity>& entities) override;
    };

    class ITexture {
    public:
        virtual SDL_Texture* getSDLTexture() = 0;
        virtual SDL_Rect getTextureSize() const = 0;
        virtual ~ITexture() = default;
    };

    class Texture : public ITexture {
    private:
        SDL_Texture* texture = nullptr;
    public:
        Texture(SDL_Texture* texture) : texture(texture) {}
        static Texture loadTexture(SDL_Renderer* renderer, const std::string& path);
        Texture(const Texture&) = delete;
        Texture(const Texture&& texture) noexcept : texture(texture.texture) {}
        Texture& operator=(const Texture&) = delete;
        Texture& operator=(Texture&&) noexcept;
        ~Texture() override;
        SDL_Texture* getSDLTexture() override { return this->texture; }
        SDL_Rect getTextureSize() const override;

    };

    class Sprite : public world::Component {
    private:
        std::unique_ptr<ITexture> texture;
        const float avgFrameTime = 0;
        int spriteCount = 0;
        int currentSprite = 0;
        const std::vector<SDL_Rect> sprites;
        const std::vector<SDL_Rect> getAnimationRects();
        std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> lastUpdate;
        bool isPastFrameTime(
            std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> time
        ) const;
    public:
        Sprite(std::unique_ptr<ITexture>&& texture, int spriteCount, float duration);
        const SDL_Rect getNextRect(
            std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> currentTime
        );
        std::unique_ptr<ITexture>& getTexture();
    };
}

#endif