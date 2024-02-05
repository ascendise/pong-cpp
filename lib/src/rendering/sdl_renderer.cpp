#include <rendering.hpp>

namespace pong::rendering {

SDLRenderer::SDLRenderer(SDLWindow &&window) : window(std::move(window)) {
  auto rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE;
  this->renderer = SDL_CreateRenderer(*window, 0, rendererFlags);
}

SDLRenderer::SDLRenderer(SDLRenderer &&renderer) noexcept : window(std::move(renderer.window)), renderer(*renderer) { }

SDLRenderer &SDLRenderer::operator=(SDLRenderer &&renderer) noexcept {
	this->window = std::move(renderer.window);
	this->renderer = *renderer;
	return *this;
}

SDL_Renderer *SDLRenderer::operator*() {
	return this->renderer;
}

SDLRenderer::~SDLRenderer() {
	SDL_DestroyRenderer(this->renderer);
}

} // namespace pong::rendering
