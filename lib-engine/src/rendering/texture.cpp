#include <rendering.hpp>

#include <SDL_image.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <array>
#include <string>

namespace pong::rendering {

Texture::Texture(Texture &&other) noexcept {
  if (this != &other) {
    this->texture = other.texture;
    other.texture = nullptr;
  }
}

Texture Texture::loadTexture(SDL_Renderer *renderer, const std::string &path) {
  auto *surface = IMG_Load(path.c_str());
  auto *sdlTexture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  return Texture(sdlTexture);
}

Texture Texture::createTexture(SDL_Renderer *renderer, const std::array<unsigned char, 4> rgba,
                               const math::Vector2D size) {
  SDL_Texture *sdlTexture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, (int)size.x, (int)size.y);
  colorTexture(sdlTexture, rgba, size);
  return Texture(sdlTexture);
}

void Texture::colorTexture(SDL_Texture *sdlTexture, const std::array<unsigned char, 4> rgba, math::Vector2D size) {
  // NOLINTBEGIN Doing couple things that clang-tidy doesn't like, but this is just the way to do it...
  unsigned char *pixels = nullptr;
  int pitch = 0;
  SDL_LockTexture(sdlTexture, nullptr, (void **)&pixels, &pitch);
  int bufferSize = size.x * size.y * sizeof(rgba);
  for (int i = 0; i < bufferSize; i += sizeof(rgba)) {
    memcpy(&pixels[i], &rgba, sizeof(rgba));
  }
  SDL_UnlockTexture(sdlTexture);
  // NOLINTEND
}

SDL_Rect Texture::getTextureSize() const {
  SDL_Rect size = {0, 0, 0, 0};
  SDL_QueryTexture(texture, nullptr, nullptr, &size.w, &size.h);
  return size;
}

Texture &Texture::operator=(Texture &&other) noexcept {
  if (this != &other) {
    this->texture = other.texture;
    other.texture = nullptr;
  }
  return *this;
}

Texture::~Texture() {
  if (this->texture)
    SDL_DestroyTexture(this->texture);
};
} // namespace pong::rendering
