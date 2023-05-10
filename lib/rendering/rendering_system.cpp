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
                    auto sdlTexture = sprite->GetTexture()->GetTexture();
                    auto textureRect = sprite->GetNextRect();
                    SDL_Rect renderRect = { 
                        position->getX(), 
                        position->getY(), 
                        textureRect.w, 
                        textureRect.h 
                    };
                    SDL_RenderCopy(renderer, sdlTexture, &textureRect, &renderRect);
                }
            }
        }
    }
}