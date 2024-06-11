#include "multimedia.hpp"

namespace pong::multimedia {

void KeyEventProcessor::process(const world::events::Event &event) {
  try {
    const auto &keyEvent = dynamic_cast<const KeyEvent &>(event);
    for (auto &playerControl : keyEvent.getPlayerControls())
      playerControl.get().handleKeyEvent(keyEvent);
  } catch (std::bad_cast &) {
    // None of our business
  }
}

} // namespace pong::multimedia