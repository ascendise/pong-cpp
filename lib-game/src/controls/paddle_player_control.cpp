#include "controls.hpp"
#include <SDL_events.h>
#include <math.hpp>
#include <multimedia.hpp>

namespace pong::game::controls {

void PaddlePlayerControl::handleKeyEvent(const multimedia::KeyEvent &keyEvent) {
  SDL_KeyboardEvent sdlKeyEvent = keyEvent.getSdlKeyboardEvent();
  math::Vector2D velocity = playerRigidBody.getVelocity();
  float speed = sdlKeyEvent.state == SDL_PRESSED ? 100 : 0;
  switch (sdlKeyEvent.keysym.sym) {
  case SDLK_w:
    velocity.y = speed;
    break;
  case SDLK_s:
    velocity.y = speed * -1;
    break;
  }
  playerRigidBody.setVelocity(velocity);
}

void PaddlePlayerControl::changeVelocity(math::Vector2D &velocity, const SDL_KeyboardEvent &keyEvent) {}

} // namespace pong::game::controls