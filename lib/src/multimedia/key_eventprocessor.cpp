#include "multimedia.hpp"

namespace pong::multimedia {

void KeyEventProcessor::process(const world::events::Event &event) {
  try {
    const auto &keyEvent = dynamic_cast<const KeyEvent &>(event);
    for (const auto &entity : this->entities) {
      auto playerControlOption = entity.getComponent<IPlayerControl>();
      if (playerControlOption.has_value())
        playerControlOption->get().handleKeyEvent(keyEvent);
    }
  } catch (std::bad_cast &) {
    // None of our business
  }
}

} // namespace pong::multimedia