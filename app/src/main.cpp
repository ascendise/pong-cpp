#include <controls.hpp>

#include <components.hpp>
#include <events.hpp>
#include <math.hpp>
#include <multimedia.hpp>
#include <physics.hpp>
#include <rendering.hpp>
#include <world.hpp>

#include <SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_main.h>
#include <SDL_render.h>
#include <SDL_video.h>

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

int main(int /*argc*/, char * /*argv*/[]) {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  pong::rendering::SDLWindow window(pong::math::Vector2D(1280, 720), pong::rendering::WindowPosition::Centered, "Pong");
  pong::rendering::SDLRenderer renderer(std::move(window));
  // World + EventQueue
  pong::world::events::EventQueue eventQueue;
  eventQueue.registerProcessor(std::make_unique<pong::physics::CollisionEventProcessor>());
  auto sdlSystemControl = std::make_unique<pong::multimedia::SDLSystemControl>();
  eventQueue.registerProcessor(std::make_unique<pong::multimedia::SystemEventProcessor>(std::move(sdlSystemControl)));
  eventQueue.registerProcessor(std::make_unique<pong::multimedia::KeyEventProcessor>());
  pong::world::World world(std::make_unique<pong::world::events::EventQueue>(std::move(eventQueue)));
  // Background
  std::vector<std::shared_ptr<pong::world::Component>> backgroundComponents;
  backgroundComponents.push_back(std::make_shared<pong::world::Position>(0, 0));
  auto texture = pong::rendering::Texture::loadTexture(
      *renderer, "../../assets/Background.png"); // TODO: Fix assets being in different directory for Windows
  backgroundComponents.push_back(
      std::make_shared<pong::rendering::Sprite>(std::make_unique<pong::rendering::Texture>(std::move(texture)), 1, 0));
  world.registerEntity(backgroundComponents);
  // Ball
  std::vector<std::shared_ptr<pong::world::Component>> ballComponents;
  ballComponents.push_back(std::make_shared<pong::world::Position>(-200, 200));
  auto ballTexture = pong::rendering::Texture::loadTexture(*renderer, "../../assets/anim_test.png");
  ballComponents.push_back(std::make_shared<pong::rendering::Sprite>(
      std::make_unique<pong::rendering::Texture>(std::move(ballTexture)), 4, 0.1));
  auto ballBody = std::make_shared<pong::physics::RigidBody>(pong::math::Vector2D(150, -150), 1);
  ballComponents.push_back(ballBody);
  ballComponents.push_back(
      std::make_shared<pong::physics::BoxCollider>(pong::world::Position(-200, 200), pong::math::Vector2D(50, 400)));
  world.registerEntity(ballComponents);
  // Wall
  std::vector<std::shared_ptr<pong::world::Component>> wallComponents;
  wallComponents.push_back(std::make_shared<pong::world::Position>(300, 0));
  auto wallBody = std::make_shared<pong::physics::RigidBody>(pong::math::Vector2D(0, 0), 1);
  wallComponents.push_back(std::make_shared<pong::game::controls::PaddlePlayerControl>(*wallBody));
  wallComponents.push_back(wallBody);
  wallComponents.push_back(
      std::make_shared<pong::physics::BoxCollider>(pong::world::Position(300, 0), pong::math::Vector2D(64, 64)));
  auto wallTexture = pong::rendering::Texture::loadTexture(*renderer, "../../assets/wall.png");
  wallComponents.push_back(std::make_shared<pong::rendering::Sprite>(
      std::make_unique<pong::rendering::Texture>(std::move(wallTexture)), 1, 0));
  world.registerEntity(wallComponents);
  // Systems
  world.registerSystem(std::make_unique<pong::physics::MovementSystem>(world.getClock()));
  world.registerSystem(std::make_unique<pong::rendering::RenderingSystem>(std::move(renderer), world.getClock()));
  world.registerSystem(std::make_unique<pong::physics::CollisionSystem>(world.getEventQueue()));
  world.registerSystem(std::make_unique<pong::multimedia::MultimediaSystem>(world.getEventQueue()));
  while (true)
    world.run();
  SDL_Quit();
  return 0;
}
