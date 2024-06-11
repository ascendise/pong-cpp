#include "multimedia.hpp"
#include <SDL.h>
#include <iostream>
#include <memory>
#include <typeinfo>
namespace pong::multimedia {

void SystemEventProcessor::process(const world::events::Event &event) {
  try {
    const auto &systemEvent = dynamic_cast<const SystemEvent &>(event);
    if (systemEvent.getAction() == QuitAppEvent::ACTION) {
      systemControl->exit();
    }
  } catch (std::bad_cast &) {
    // Do nothing. Event is not meant for this processor
  }
}

} // namespace pong::multimedia
