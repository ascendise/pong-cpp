#ifndef RENDERING_HPP
#define RENDERING_HPP

#include "math.hpp"
#include <SDL_video.h>
#include <components.hpp>
#include <tuple>
#include <world.hpp>

#include <SDL.h>
#include <stdexcept>
#include <string>

namespace pong::rendering {

class ScreenPositionCalculator {
private:
  SDL_Surface *windowSurface;
  SDL_Rect getWindowSize() const;

public:
  ScreenPositionCalculator(SDL_Surface *windowSurface) : windowSurface(windowSurface) {}
  SDL_Rect toScreenPosition(const world::Position &position);
  world::Position toWorldPosition(const SDL_Rect &screenPosition);
};

enum class WindowPosition { Centered };

std::tuple<int, int> getSDLWindowPosition(WindowPosition position);

class SDLWindow {
private:
  SDL_Window *window = nullptr;
public:
  SDLWindow(math::Vector2D size, WindowPosition position, std::string title);
  SDLWindow(const SDLWindow &window) = delete;
  SDLWindow(SDLWindow &&window) noexcept;
  SDLWindow &operator=(const SDLWindow &window) = delete;
  SDLWindow &operator=(SDLWindow &&window) noexcept;
  SDL_Window *operator*() noexcept;
  ~SDLWindow();
};

class SDLRenderer {
private:
  SDL_Renderer *renderer = nullptr;
  SDLWindow window;
public:
  SDLRenderer(SDLWindow &&window);
  SDLRenderer(const SDLRenderer &renderer) = delete;
  SDLRenderer(SDLRenderer &&renderer) noexcept;
  SDLRenderer &operator=(const SDLRenderer &renderer) = delete;
  SDLRenderer &operator=(SDLRenderer &&renderer) noexcept;
	SDL_Renderer *operator*() noexcept;
  ~SDLRenderer();
};

class RenderingSystem : public world::System {
private:
	SDLRenderer renderer;
  ScreenPositionCalculator screenCalc;
  world::IReadOnlyClock &clock;
  static SDL_Surface *getSurface(SDL_Renderer *renderer);

public:
  RenderingSystem(SDLRenderer &&renderer, world::IReadOnlyClock &clock)
      : renderer(std::move(renderer)), clock(clock), screenCalc(getSurface(*renderer)) {}
  void run(std::vector<world::Entity> &entities) override;
};

class ITexture {
public:
  virtual SDL_Texture *getSDLTexture() = 0;
  virtual SDL_Rect getTextureSize() const = 0;
  virtual ~ITexture() = default;
};

class Texture : public ITexture {
private:
  SDL_Texture *texture = nullptr;

public:
  Texture(SDL_Texture *texture) : texture(texture) {}
  static Texture loadTexture(SDL_Renderer *renderer, const std::string &path);
  Texture(const Texture &) = delete;
  Texture(const Texture &&texture) noexcept : texture(texture.texture) {}
  Texture &operator=(const Texture &) = delete;
  Texture &operator=(Texture &&) noexcept;
  ~Texture() override;
  SDL_Texture *getSDLTexture() override { return this->texture; }
  SDL_Rect getTextureSize() const override;
};

class Sprite : public world::Component {
private:
  std::unique_ptr<ITexture> texture;
  const float avgFrameTime = 0;
  int spriteCount = 0;
  int currentSprite = 0;
  const std::vector<SDL_Rect> sprites;
  const std::vector<SDL_Rect> getAnimationRects();
  std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> lastUpdate;
  bool
  isPastFrameTime(std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> time) const;

public:
  Sprite(std::unique_ptr<ITexture> &&texture, int spriteCount, float duration);
  const SDL_Rect
  getNextRect(std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> currentTime);
  std::unique_ptr<ITexture> &getTexture();
};
} // namespace pong::rendering

#endif
