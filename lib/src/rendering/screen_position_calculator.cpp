#include <components.hpp>
#include <rendering.hpp>

#include <SDL_rect.h>

namespace pong::rendering {

SDL_Rect ScreenPositionCalculator::toScreenPosition(const world::Position &position) {
  auto window = getWindowSize();
  SDL_Rect screenPosition{};
  screenPosition.x = (int)(position.x + (float)window.w / 2.0f);
  screenPosition.y = (int)(position.y + (float)window.h / 2.0f);
  return screenPosition;
}

SDL_Rect ScreenPositionCalculator::getWindowSize() const {
  SDL_Rect window{};
  window.w = this->windowSurface->w;
  window.h = this->windowSurface->h;
  return window;
}

world::Position ScreenPositionCalculator::toWorldPosition(const SDL_Rect &screenPosition) {
  auto window = getWindowSize();
  return world::Position((float)screenPosition.x - (float)window.w / 2.0f,
                         (float)screenPosition.y - (float)window.h / 2.0f);
}
} // namespace pong::rendering