#ifndef MULTIMEDIA_HPP
#define MULTIMEDIA_HPP

#include "events.hpp"
#include "world.hpp"
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
  const std::string &getAction() const;
};

/// @brief Informs the World that the Player wants to exit the application
class QuitAppEvent : public SystemEvent {
public:
  static const std::string ACTION;
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

} // namespace pong::multimedia

#endif
