#ifndef SDL_SYSTEM_CONTROL_CPP
#define SDL_SYSTEM_CONTROL_CPP

#include "multimedia.hpp"
#include <SDL.h>

namespace pong::multimedia {

void SDLSystemControl::exit() { SDL_Quit(); }

} // namespace pong::multimedia

#endif
