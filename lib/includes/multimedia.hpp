#ifndef MULTIMEDIA_HPP
#define MULTIMEDIA_HPP

#include "events.hpp"
#include "world.hpp"
namespace pong::multimedia {

/// @brief handles events from SDL and creates appropriate world events for it.
class MultimediaSystem : public world::System {
private:
  world::events::IEventQueuePort &eventQueue;

public:
  MultimediaSystem(world::events::IEventQueuePort &eventQueue) : eventQueue(eventQueue) {}
  void run(std::vector<world::Entity> &entities) override;
};

} // namespace pong::multimedia

#endif
