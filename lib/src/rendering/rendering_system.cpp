#include "rendering.hpp"
#include <components.hpp>
#include <world.hpp>

#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <vector>

namespace pong::rendering {

SDL_Surface *RenderingSystem::getSurface(SDL_Renderer *renderer) {
  auto *window = SDL_RenderGetWindow(renderer);
  return SDL_GetWindowSurface(window);
}

void RenderingSystem::run(std::vector<world::Entity> &entities) {
	SDL_RenderClear(*renderer);
  for (auto &entity : entities) {
    auto positionOption = entity.getComponent<pong::world::Position>();
    auto spriteOption = entity.getComponent<pong::rendering::Sprite>();
    if (positionOption.has_value() && spriteOption.has_value()) {
      auto &position = positionOption.value().get();
      auto renderRect = screenCalc.toScreenPosition(position);
      auto &sprite = spriteOption.value().get();
      auto textureRect = sprite.getNextRect(clock.now());
      renderRect.x -= textureRect.w / 2;
      renderRect.y -= textureRect.h / 2;
      renderRect.w = textureRect.w;
      renderRect.h = textureRect.h;
      auto *sdlTexture = sprite.getTexture()->getSDLTexture();
      SDL_RenderCopy(*renderer, sdlTexture, &textureRect, &renderRect);
    }
  }
	SDL_RenderPresent(*renderer);
}

} // namespace pong::rendering
