#include <SDL.h>
#include <array>
#include <controls.hpp>
#include <physics.hpp>
#include <prefabs.hpp>
#include <rendering.hpp>

namespace pong::prefabs {

void Prefabs::registerBackground(world::World &world, rendering::SDLRenderer &renderer) {
  std::vector<std::shared_ptr<world::Component>> components;
  components.push_back(std::make_shared<world::Position>(0.0f, 0.0f));
  rendering::Texture texture = rendering::Texture::loadTexture(
      *renderer, "../../assets/Background.png"); // TODO: Fix assets being in deeper directory on Windows build
  rendering::Sprite sprite(std::make_unique<rendering::Texture>(std::move(texture)), 1.0f, 0.0f);
  components.push_back(std::make_shared<rendering::Sprite>(std::move(sprite)));
  world.registerEntity(components);
}

void Prefabs::registerBall(world::World &world, rendering::SDLRenderer &renderer) {
  std::vector<std::shared_ptr<world::Component>> components;
  auto position = std::make_shared<world::Position>(0.0f, 0.0f);
  components.push_back(position);
  rendering::Texture texture = rendering::Texture::loadTexture(*renderer, "../../assets/anim_test.png");
  rendering::Sprite sprite(std::make_unique<rendering::Texture>(std::move(texture)), 4.0f, 0.1f);
  components.push_back(std::make_shared<rendering::Sprite>(std::move(sprite)));
  auto rigidBody = std::make_shared<physics::RigidBody>(math::Vector2D(200.0f, 100.0f), 0.0f);
  components.push_back(rigidBody);
  auto collider = std::make_shared<physics::BoxCollider>(*position, math::Vector2D(64.0f, 64.0f));
  components.push_back(collider);
  world.registerEntity(components);
}

void Prefabs::registerPaddle(world::World &world, rendering::SDLRenderer &renderer) {
  std::vector<std::shared_ptr<world::Component>> components;
  auto position = std::make_shared<world::Position>(-500.0f, 0.0f);
  components.push_back(position);
  auto rigidBody = std::make_shared<physics::RigidBody>(math::Vector2D(0.0f, 0.0f), 1.0f);
  components.push_back(rigidBody);
  components.push_back(std::make_shared<game::controls::PaddlePlayerControl>(*rigidBody));
  auto collider = std::make_shared<physics::BoxCollider>(*position, math::Vector2D(50.0f, 400.0f));
  components.push_back(collider);
  auto texture = rendering::Texture::loadTexture(*renderer, "../../assets/wall.png");
  auto sprite = std::make_shared<rendering::Sprite>(std::make_unique<rendering::Texture>(std::move(texture)), 1, 0.0f);
  components.push_back(std::move(sprite));
  world.registerEntity(components);
}

void Prefabs::registerInvisibleWall(world::World &world, pong::rendering::SDLRenderer &renderer,
                                    const world::Position &position, const math::Vector2D &size) {
  std::vector<std::shared_ptr<world::Component>> wallComponents;
  wallComponents.push_back(std::make_shared<world::Position>(position));
  wallComponents.push_back(std::make_shared<physics::RigidBody>(math::Vector2D(0.0f, 0.0f), 1.0f));
  wallComponents.push_back(std::make_shared<physics::BoxCollider>(position, size));
  auto texture =
      std::make_unique<rendering::Texture>(rendering::Texture::createTexture(*renderer, {255, 0, 0, 255}, size));
  wallComponents.push_back(std::make_shared<rendering::Sprite>(std::move(texture), 1, 0.0f));
  world.registerEntity(wallComponents);
}

} // namespace pong::prefabs