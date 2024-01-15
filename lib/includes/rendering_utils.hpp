#ifndef RENDERING_UTILS_HPP
#define RENDERING_UTILS_HPP

#include <world.hpp>
#include <rendering.hpp>
#include <components.hpp>
#include <SDL.h>


namespace pong {
	namespace rendering {

		class ScreenPositionCalculator {
		private:
			SDL_Surface* windowSurface;
			SDL_Rect getWindowSize() const;
		public:
			ScreenPositionCalculator(SDL_Surface* windowSurface) : windowSurface(windowSurface) {}
			SDL_Rect toScreenPosition(world::Position position);
			world::Position toWorldPosition(SDL_Rect  screenPosition);
		};

	}
}

#endif