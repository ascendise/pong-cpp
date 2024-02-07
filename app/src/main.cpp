#include "multimedia.hpp"
#include <components.hpp>
#include <events.hpp>
#include <math.hpp>
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

void runGameLoop(pong::world::World &world);

int main(int /*argc*/, char * /*argv*/[]) {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  pong::rendering::SDLWindow window(pong::math::Vector2D(1280, 720), pong::rendering::WindowPosition::Centered, "Pong");
  pong::rendering::SDLRenderer renderer(std::move(window));
  // World + EventQueue
  pong::world::events::EventQueue eventQueue;
  eventQueue.registerProcessor(std::make_unique<pong::physics::CollisionEventProcessor>());
  pong::world::World world(std::make_unique<pong::world::events::EventQueue>(std::move(eventQueue)));
  // Background
  std::vector<std::unique_ptr<pong::world::Component>> backgroundComponents;
  backgroundComponents.push_back(std::make_unique<pong::world::Position>(0, 0));
  auto texture = pong::rendering::Texture::loadTexture(*renderer, "../assets/Background.png");
  backgroundComponents.push_back(
      std::make_unique<pong::rendering::Sprite>(std::make_unique<pong::rendering::Texture>(std::move(texture)), 1, 0));
  world.registerEntity(std::move(backgroundComponents));
  // Ball
  std::vector<std::unique_ptr<pong::world::Component>> ballComponents;
  ballComponents.push_back(std::make_unique<pong::world::Position>(0, 0));
  auto ballTexture = pong::rendering::Texture::loadTexture(*renderer, "../assets/anim_test.png");
  ballComponents.push_back(std::make_unique<pong::rendering::Sprite>(
      std::make_unique<pong::rendering::Texture>(std::move(ballTexture)), 4, 0.1));
  pong::physics::RigidBody ballBody;
  ballBody.setBounce(1);
  ballBody.setVelocity(pong::math::Vector2D(250, 250));
  ballComponents.push_back(std::make_unique<pong::physics::RigidBody>(std::move(ballBody)));
  ballComponents.push_back(
      std::make_unique<pong::physics::BoxCollider>(pong::world::Position(0, 0), pong::math::Vector2D(64, 64)));
  world.registerEntity(std::move(ballComponents));
  // Invisible Middle Wall (Vertical)
  std::vector<std::unique_ptr<pong::world::Component>> wallComponents;
  wallComponents.push_back(std::make_unique<pong::world::Position>(300, 0));
  pong::physics::RigidBody wallBody;
  wallBody.setBounce(1);
  wallBody.setVelocity(pong::math::Vector2D(0, 0));
  wallComponents.push_back(std::make_unique<pong::physics::RigidBody>(std::move(wallBody)));
  wallComponents.push_back(
      std::make_unique<pong::physics::BoxCollider>(pong::world::Position(300, 0), pong::math::Vector2D(64, 64)));
  auto wallTexture = pong::rendering::Texture::loadTexture(*renderer, "../assets/wall.png");
  wallComponents.push_back(std::make_unique<pong::rendering::Sprite>(
      std::make_unique<pong::rendering::Texture>(std::move(wallTexture)), 1, 0));
  world.registerEntity(std::move(wallComponents));
  // Systems
  world.registerSystem(std::make_unique<pong::physics::MovementSystem>(world.getClock()));
  world.registerSystem(std::make_unique<pong::rendering::RenderingSystem>(std::move(renderer), world.getClock()));
  world.registerSystem(std::make_unique<pong::physics::CollisionSystem>(world.getEventQueue()));
	world.registerSystem(std::make_unique<pong::multimedia::MultimediaSystem>(world.getEventQueue()));
  runGameLoop(world);
  SDL_Quit();
  return 0;
}

void runGameLoop(pong::world::World &world) {
  SDL_Event event;
  while (true) {
    world.run();
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        return;
      }
    }
  }
}
