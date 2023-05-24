#include "rendering.hpp"
#include "../world/components.hpp"
#include <stdexcept>
#include <SDL.h>

namespace pong {
    namespace rendering {
        RenderingSystem::RenderingSystem(SDL_Renderer* renderer) {
            this->renderer = renderer;
        }

        void RenderingSystem::run(std::vector<std::shared_ptr<pong::world::Entity>> entities) {
            for(auto& entity : entities) {
                auto position = entity->getComponent<pong::world::Position>();
                auto sprite = entity->getComponent<pong::rendering::Sprite>();
                if (position && sprite) {
                    auto sdlTexture = sprite->getTexture()->getSDLTexture();
                    auto textureRect = sprite->getNextRect();
                    SDL_Rect renderRect = { 
                        (int)position->x, 
                        (int)position->y, 
                        textureRect.w, 
                        textureRect.h 
                    };
                    SDL_RenderCopy(renderer, sdlTexture, &textureRect, &renderRect);
                }
            }
        }
    }
}