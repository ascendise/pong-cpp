#include "SDL_events.h"
#include "multimedia.hpp"

namespace pong::multimedia {

SDL_KeyboardEvent KeyEvent::getSdlKeyboardEvent() const { return this->keyboardEvent; }

} // namespace pong::multimedia
