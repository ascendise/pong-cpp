#include "rendering.hpp"
#include "../world/components.hpp"
#include <stdexcept>
#include <SDL.h>

namespace pong {
    namespace rendering {
        RenderingSystem::RenderingSystem(SDL_Renderer* renderer) {
            this->renderer = renderer;
            this->screenCalc = std::make_unique<ScreenPositionCalculator>(getSurface(renderer));
            this->clock.start();
        }

        std::shared_ptr<Surface> RenderingSystem::getSurface(SDL_Renderer* renderer) {
            auto window = SDL_RenderGetWindow(renderer);
            auto sdlSurface = SDL_GetWindowSurface(window);
            return std::make_shared<Surface>(sdlSurface);
        }

        void RenderingSystem::run(std::vector<std::shared_ptr<pong::world::Entity>> entities) {
            for(auto& entity : entities) {
                auto position = entity->getComponent<pong::world::Position>();
                auto sprite = entity->getComponent<pong::rendering::Sprite>();
                if (position && sprite) {
                    auto sdlTexture = sprite->getTexture()->getSDLTexture();
                    auto textureRect = sprite->getNextRect(clock.now());
                    auto renderRect = screenCalc->toScreenPosition(*position);
                    renderRect.x -= textureRect.w / 2;
                    renderRect.y -= textureRect.h / 2;
                    renderRect.w = textureRect.w;
                    renderRect.h = textureRect.h;
                    SDL_RenderCopy(renderer, sdlTexture, &textureRect, &renderRect);
                }
            }
        }
    }
}