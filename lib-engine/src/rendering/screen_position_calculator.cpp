#include <components.hpp>
#include <rendering.hpp>

#include <SDL_rect.h>

namespace pong::rendering {

SDL_Rect ScreenPositionCalculator::toScreenPosition(const world::Position &position) {
  auto window = getWindowSize();
  SDL_Rect screenPosition{};
  float middleWidth = (float)window.w / 2.0f;
  float middleHeight = (float)window.h / 2.0f;
  screenPosition.x = (int)(position.x + middleWidth);
  screenPosition.y = (int)((position.y * -1) + middleHeight);
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
  float middleWidth = (float)window.w / 2.0f;
  float middleHeight = (float)window.h / 2.0f;
  return world::Position((float)screenPosition.x - middleWidth, middleHeight - (float)screenPosition.y);
}
} // namespace pong::rendering