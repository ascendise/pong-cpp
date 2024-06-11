#include "multimedia.hpp"
#include <SDL_events.h>
#include <iostream>
#include <vector>
namespace pong::multimedia {

std::vector<std::reference_wrapper<IPlayerControl>> getPlayerControls(std::vector<world::Entity> &entities);

void MultimediaSystem::run(std::vector<world::Entity> &entities) {
  SDL_Event event;
  auto playerControls = getPlayerControls(entities);
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_KEYUP:
    case SDL_KEYDOWN:
      eventQueue.enqueue(std::make_shared<KeyEvent>(event.key, playerControls));
      break;
    case SDL_QUIT:
      eventQueue.enqueue(std::make_shared<QuitAppEvent>());
      break;
    }
  }
}

std::vector<std::reference_wrapper<IPlayerControl>> getPlayerControls(std::vector<world::Entity> &entities) {
  std::vector<std::reference_wrapper<IPlayerControl>> playerControls;
  for (world::Entity &entity : entities) {
    auto playerControlOption = entity.getComponent<IPlayerControl>();
    if (playerControlOption.has_value()) {
      playerControls.push_back(*playerControlOption);
    }
  }
  return playerControls;
}

} // namespace pong::multimedia
