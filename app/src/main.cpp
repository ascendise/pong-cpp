#include <controls.hpp>

#include <components.hpp>
#include <events.hpp>
#include <math.hpp>
#include <multimedia.hpp>
#include <physics.hpp>
#include <prefabs.hpp>
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
  SDL_Rect windowSize{};
  SDL_GetWindowSize(*window, &windowSize.w, &windowSize.h);
  pong::rendering::SDLRenderer renderer(std::move(window));
  // World + EventQueue
  pong::world::events::EventQueue eventQueue;
  eventQueue.registerProcessor(std::make_unique<pong::physics::CollisionEventProcessor>());
  auto sdlSystemControl = std::make_unique<pong::multimedia::SDLSystemControl>();
  eventQueue.registerProcessor(std::make_unique<pong::multimedia::SystemEventProcessor>(std::move(sdlSystemControl)));
  eventQueue.registerProcessor(std::make_unique<pong::multimedia::KeyEventProcessor>());
  pong::world::World world(std::make_unique<pong::world::events::EventQueue>(std::move(eventQueue)));
  // Create entities
  pong::prefabs::Prefabs::registerBackground(world, renderer);
  pong::prefabs::Prefabs::registerBall(world, renderer);
  pong::prefabs::Prefabs::registerPaddle(world, renderer);
  pong::world::Position topMiddle(0, (float)windowSize.h / 2.0f);
  pong::world::Position bottomMiddle(topMiddle * -1);
  pong::world::Position rightMiddle((float)windowSize.w / 2.0f, 0);
  pong::world::Position leftMiddle(rightMiddle * -1);
  pong::prefabs::Prefabs::registerInvisibleWall(world, renderer, topMiddle,
                                                pong::math::Vector2D((float)windowSize.w, 10.0f));
  pong::prefabs::Prefabs::registerInvisibleWall(world, renderer, bottomMiddle,
                                                pong::math::Vector2D((float)windowSize.w, 10.0f));
  pong::prefabs::Prefabs::registerInvisibleWall(world, renderer, leftMiddle,
                                                pong::math::Vector2D(10.0f, (float)windowSize.h - 12.0f));
  pong::prefabs::Prefabs::registerInvisibleWall(world, renderer, rightMiddle,
                                                pong::math::Vector2D(10.0f, (float)windowSize.h - 12.0f));
  // Systems
  world.registerSystem(std::make_unique<pong::physics::MovementSystem>(world.getClock()));
  world.registerSystem(std::make_unique<pong::rendering::RenderingSystem>(std::move(renderer), world.getClock()));
  world.registerSystem(std::make_unique<pong::physics::CollisionSystem>(world.getEventQueue()));
  world.registerSystem(std::make_unique<pong::multimedia::MultimediaSystem>(world.getEventQueue()));
  // Game Loop
  while (true)
    world.run();
  return 0;
}
