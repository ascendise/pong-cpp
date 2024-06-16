#include <rendering.hpp>

namespace pong::rendering {

SDLWindow::SDLWindow(math::Vector2D size, WindowPosition position, std::string title) {
  auto sdlPosition = getSDLWindowPosition(position);
  this->window =
      SDL_CreateWindow(title.data(), std::get<0>(sdlPosition), std::get<1>(sdlPosition), (int)size.x, (int)size.y, 0);
}

SDLWindow::SDLWindow(SDLWindow &&other) noexcept : window(*other) {
  if (this != &other) {
    this->window = other.window;
    other.window = nullptr;
  }
}

SDLWindow &SDLWindow::operator=(SDLWindow &&other) noexcept {
  if (this != &other) {
    this->window = *other;
    other.window = nullptr;
  }
  return *this;
}

SDL_Window *SDLWindow::operator*() noexcept { return this->window; }

SDLWindow::~SDLWindow() {
  if (this->window)
    SDL_DestroyWindow(this->window);
}

} // namespace pong::rendering
