#include "multimedia.hpp"
#include <SDL_events.h>
#include <iostream>
#include <vector>
namespace pong::multimedia {

void MultimediaSystem::run(std::vector<world::Entity>&  /*entities*/) {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				exit(0); //NOLINT FIXME
		}
	}
}

}
