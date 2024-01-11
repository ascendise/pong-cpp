#ifndef FAKE_SURFACE
#define FAKE_SURFACE

#include <SDL.h>
#include <rendering/utils.hpp>

namespace pong {
	namespace rendering {

		class FakeSurface : public ISurface {
		private:
			int width;
			int height;
		public:
			FakeSurface(int width, int height) : width(width), height(height) {}
			SDL_Rect getWindowSize() {
				SDL_Rect window{};
				window.w = width;
				window.h = height;
				return window;
			}
		};
	}
}

#endif