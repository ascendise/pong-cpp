#include <rendering.hpp>

namespace pong::rendering {

SDLRenderer::SDLRenderer(SDLWindow &&window) : window(std::move(window)) {
  auto rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE;
  this->renderer = SDL_CreateRenderer(*this->window, 0, rendererFlags);
}

SDLRenderer::SDLRenderer(SDLRenderer &&other) noexcept : window(std::move(other.window)) {
  if (this != &other) {
    this->renderer = other.renderer;
    other.renderer = nullptr;
  }
}

SDLRenderer &SDLRenderer::operator=(SDLRenderer &&other) noexcept {
  if (this != &other) {
    this->window = std::move(other.window);
    this->renderer = *other;
    other.renderer = nullptr;
  }
  return *this;
}

SDL_Renderer *SDLRenderer::operator*() noexcept { return this->renderer; }

SDLRenderer::~SDLRenderer() {
  if (this->renderer)
    SDL_DestroyRenderer(this->renderer);
}

} // namespace pong::rendering
