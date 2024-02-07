#include "multimedia.hpp"
#include <SDL.h>
#include <iostream>
#include <typeinfo>
namespace pong::multimedia {

void SystemEventProcessor::process(const world::events::Event &event) {
	try {
		const auto &quitEvent = dynamic_cast<const QuitAppEvent &>(event);
		SDL_Quit();
	}	catch (std::bad_cast&) {
		//Do nothing. Event is not meant for this processor
	}
}

} // namespace pong::multimedia
