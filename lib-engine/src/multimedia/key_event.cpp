#include "SDL_events.h"
#include "multimedia.hpp"

namespace pong::multimedia {

SDL_KeyboardEvent KeyEvent::getSdlKeyboardEvent() const { return this->keyboardEvent; }

std::vector<std::reference_wrapper<IPlayerControl>> KeyEvent::getPlayerControls() const { return this->playerControls; }

} // namespace pong::multimedia
