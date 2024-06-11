#ifndef GAME_CONTROLS_HPP
#define GAME_CONTROLS_HPP

#include "multimedia.hpp"
#include "physics.hpp"
#include "world.hpp"
#include <SDL_events.h>

namespace pong::game::controls {

class PaddlePlayerControl : public multimedia::IPlayerControl {
private:
  physics::RigidBody &playerRigidBody;
  void changeVelocity(math::Vector2D &velocity, const SDL_KeyboardEvent &keyEvent);

public:
  PaddlePlayerControl(physics::RigidBody &playerRigidBody) : playerRigidBody(playerRigidBody) {}
  void handleKeyEvent(const multimedia::KeyEvent &keyEvent);
  PaddlePlayerControl(PaddlePlayerControl &&) noexcept = default;
  PaddlePlayerControl &operator=(PaddlePlayerControl &&) noexcept = default;
};

} // namespace pong::game::controls

#endif