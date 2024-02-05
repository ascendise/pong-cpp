#include "rendering.hpp"
#include <tuple>

namespace pong::rendering {

std::tuple<int, int> getSDLWindowPosition(WindowPosition position) {
	switch(position) {
		case WindowPosition::Centered:
			return std::tuple<int, int>(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		default:
			throw std::invalid_argument("No matching position configuration found");
	}
}


} // namespace pong::rendering
