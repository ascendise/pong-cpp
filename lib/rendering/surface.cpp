#include <world/world.hpp>
#include <rendering/utils.hpp>

namespace pong {
	namespace rendering {

		Surface::Surface(SDL_Surface* surface) : surface(surface) { }

		Surface::Surface(const Surface&& ref) noexcept {
			this->surface = ref.surface;
		}

		Surface& Surface::operator=(const Surface && ref) noexcept {
			if (this != &ref) {
				this->surface = ref.surface;
			}
			return *this;
		}

		Surface::~Surface() {
			SDL_FreeSurface(this->surface);
		}

		SDL_Rect Surface::getWindowSize() {
			SDL_Rect rect{};
			rect.w = this->surface->w;
			rect.h = this->surface->h;
			return rect;
		}

	}
}