#include <rendering.hpp>
#include <world.hpp>

namespace pong::prefabs {
class Prefabs {
public:
  static void registerBackground(pong::world::World &world, pong::rendering::SDLRenderer &renderer);
  static void registerBall(pong::world::World &world, pong::rendering::SDLRenderer &renderer);
  static void registerPaddle(pong::world::World &world, pong::rendering::SDLRenderer &renderer);
  static void registerInvisibleWall(pong::world::World &world, pong::rendering::SDLRenderer &renderer,
                                    const pong::world::Position &position, const pong::math::Vector2D &size);
};
} // namespace pong::prefabs
