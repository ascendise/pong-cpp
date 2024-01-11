#ifndef RENDERING_UTILS_HPP
#define RENDERING_UTILS_HPP

#include <world/world.hpp>
#include <world/components.hpp>
#include <SDL.h>

using namespace pong::world;

namespace pong {
	namespace rendering {

		class ISurface {
		public:
			virtual SDL_Rect getWindowSize() = 0;
		};

		class Surface : public ISurface {
		private:
			SDL_Surface* surface;
		public:
			Surface(SDL_Surface* surface);
			Surface(const Surface&) = delete;
			Surface& operator=(const Surface&) = delete;
			Surface(const Surface&&) noexcept;
			Surface& operator=(const Surface&&) noexcept;
			SDL_Rect getWindowSize();
			~Surface();
		};

		class ScreenPositionCalculator {
		private:
			std::shared_ptr<ISurface> screenSurface;
		public:
			ScreenPositionCalculator(std::shared_ptr<ISurface> screenSurface);
			SDL_Rect toScreenPosition(Position position);
			Position toWorldPosition(SDL_Rect  screenPosition);
		};

	}
}

#endif