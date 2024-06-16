#ifndef MULTIMEDIA_HPP
#define MULTIMEDIA_HPP

#include "events.hpp"
#include "world.hpp"
#include <SDL_events.h>
#include <string>

namespace pong::multimedia {

/// @brief handles events from SDL and creates appropriate world events for it.
class MultimediaSystem : public world::System {
private:
  world::events::IEventQueuePort &eventQueue;

public:
  MultimediaSystem(world::events::IEventQueuePort &eventQueue) : eventQueue(eventQueue) {}
  void run(std::vector<world::Entity> &entities) override;
};

/// @brief Informs the world that a system interaction is to be executed
class SystemEvent : public world::events::Event {
private:
  const std::string actionName;

public:
  SystemEvent(std::string actionName) : actionName(std::move(actionName)) {}
  /// @brief Name of the system action.
  /// @remark E.g. QUIT_APP for quitting the application
  const std::string &getAction() const;
};

/// @brief Informs the World that the Player wants to exit the application
class QuitAppEvent : public SystemEvent {
public:
  inline static const std::string ACTION = "QUIT_APP";
  QuitAppEvent() : SystemEvent(ACTION) {}
};

/// @brief Used for interacting with the overall system
class ISystemControl {
public:
  virtual void exit() = 0;
  virtual ~ISystemControl() = default;
};

/// @brief handles SystemEvents like exiting the application
class SystemEventProcessor : public world::events::EventProcessor {
private:
  std::unique_ptr<ISystemControl> systemControl;

public:
  SystemEventProcessor(std::unique_ptr<ISystemControl> &&systemControl) : systemControl(std::move(systemControl)) {}
  void process(const world::events::Event &event) override;
};

/// @brief Handles system interactions through SDL
class SDLSystemControl : public ISystemControl {
public:
  void exit() override;
};

/// @brief Handles KeyEvents raised by system
class KeyEventProcessor : public world::events::EventProcessor {
public:
  /// @brief Runs PlayerControl through incoming KeyEvents
  /// @param event: Preferably a KeyEvent, else returns instantly
  void process(const world::events::Event &event) override;
};

class IPlayerControl;

/// @brief Event that summarizes the interaction of a user with their peripherals.
/// @remark e.g. pressing the 'P' on their keyboard
class KeyEvent : public world::events::Event {
private:
  SDL_KeyboardEvent keyboardEvent;
  std::vector<std::reference_wrapper<IPlayerControl>> playerControls;

public:
  KeyEvent(SDL_KeyboardEvent keyboardEvent, std::vector<std::reference_wrapper<IPlayerControl>> playerControls)
      : keyboardEvent(keyboardEvent), playerControls(playerControls) {}
  /// @brief Underlying event that contains the actual information about the keyboard interaction
  SDL_KeyboardEvent getSdlKeyboardEvent() const;
  std::vector<std::reference_wrapper<IPlayerControl>> getPlayerControls() const;
};

/// @brief Entity with this component can be mutated through keyboard events
class IPlayerControl : public world::Component {
public:
  virtual void handleKeyEvent(const KeyEvent &keyEvent) = 0;
  virtual ~IPlayerControl() = default;
};

} // namespace pong::multimedia

#endif
