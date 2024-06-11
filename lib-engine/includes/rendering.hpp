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

/// Converts a position between a top-left oriented coordinate (SDL) system and a cartesian coordinate system (World).
class ScreenPositionCalculator {
private:
  SDL_Surface *windowSurface;
  SDL_Rect getWindowSize() const;

public:
  /// @param windowSurface SDL_Surface of the render window.
  ScreenPositionCalculator(SDL_Surface *windowSurface) : windowSurface(windowSurface) {}

  /// @brief Converts world position to position on window.
  /// @n ex: Window { w = 800; h = 640 }, Position { x = 0, y = 0 }.
  /// @n New Position = { x = 400; y = 320 }.
  SDL_Rect toScreenPosition(const world::Position &position);

  /// @brief Converts screen position to position in the world.
  /// @n ex: Window { w = 800; h = 640 }, Position { x = 400, y = 320 }.
  /// @n New Position = { x = 0; y = 0 }.
  world::Position toWorldPosition(const SDL_Rect &screenPosition);
};

/// Pre-configured configurations for SDL Window Positioning.
enum class WindowPosition { Centered };

std::tuple<int, int> getSDLWindowPosition(WindowPosition position);

/// Wrapper around SDL_Window.
class SDLWindow {
private:
  SDL_Window *window = nullptr;

public:
  /// Creates a new SDL_Window.
  SDLWindow(math::Vector2D size, WindowPosition position, std::string title);
  SDLWindow(const SDLWindow &window) = delete;
  SDLWindow(SDLWindow &&window) noexcept;
  SDLWindow &operator=(const SDLWindow &window) = delete;
  SDLWindow &operator=(SDLWindow &&window) noexcept;

  /// @returns the internal pointer for SDL operations that require SDL_Window*.
  SDL_Window *operator*() noexcept;
  ~SDLWindow();
};

/// Wrapper around SDL_Renderer.
class SDLRenderer {
private:
  SDL_Renderer *renderer = nullptr;
  SDLWindow window;

public:
  /// Creates and SDL_Renderer with the passed SDLWindow.
  SDLRenderer(SDLWindow &&window);
  SDLRenderer(const SDLRenderer &renderer) = delete;
  SDLRenderer(SDLRenderer &&renderer) noexcept;
  SDLRenderer &operator=(const SDLRenderer &renderer) = delete;
  SDLRenderer &operator=(SDLRenderer &&renderer) noexcept;

  /// @returns the internal pointer for SDL operations that require SDL_Renderer*.
  SDL_Renderer *operator*() noexcept;
  ~SDLRenderer();
};

/// @brief System responsible for rendering and animation.
/// Uses SDL internally for all rendering-related operations.
class RenderingSystem : public world::System {
private:
  SDLRenderer renderer;
  ScreenPositionCalculator screenCalc;
  world::IReadOnlyClock &clock;
  static SDL_Surface *getSurface(SDL_Renderer *renderer);
  static void centerOriginToTopLeftOrigin(SDL_Rect &rect);

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

/// Wrapper around SDL_Texture.
class Texture : public ITexture {
private:
  SDL_Texture *texture = nullptr;

public:
  Texture(SDL_Texture *texture) : texture(texture) {}

  /// Utility function for loading an image from a path as a SDL_Texture
  /// and wrapping it in a Texture
  static Texture loadTexture(SDL_Renderer *renderer, const std::string &path);
  Texture(const Texture &) = delete;
  Texture(const Texture &&texture) noexcept : texture(texture.texture) {}
  Texture &operator=(const Texture &) = delete;
  Texture &operator=(Texture &&) noexcept;
  ~Texture() override;
  /// @returns the internal SDL_Texture*.
  SDL_Texture *getSDLTexture() override { return this->texture; }
  SDL_Rect getTextureSize() const override;
};

/// @brief Sprite sheet for handling animations
/// A Spritesheet is a strip of textures where each part can be rendered per animation avgFrameTime.
/// Sprite handles the continuation of the animation by tracking the time between frames
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
  /// @brief Creates a new Spritesheet with animation information
  /// @param texture the spritesheet with all the animation frames
  /// @param spriteCount count of all frames per sprite. Required to split the texture correctly
  /// @param duration time in seconds. How fast the animation is played.
  Sprite(std::unique_ptr<ITexture> &&texture, int spriteCount, float duration);

  /// @brief calculates the current section to be rendered inside the spritesheet
  /// @returns either returns the current frame or the next frame, if enough time has passed
  const SDL_Rect
  getNextRect(std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> currentTime);
  std::unique_ptr<ITexture> &getTexture();
};

} // namespace pong::rendering

#endif
