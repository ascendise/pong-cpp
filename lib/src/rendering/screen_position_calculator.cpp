#include <rendering_utils.hpp>

namespace pong {
	namespace rendering {
		
		SDL_Rect ScreenPositionCalculator::toScreenPosition(Position position) {
			auto window = getWindowSize();
			SDL_Rect screenPosition{};
			screenPosition.x = position.x + window.w / 2;
			screenPosition.y = position.y + window.h / 2;
			return screenPosition;
		}

		SDL_Rect ScreenPositionCalculator::getWindowSize() const {
			SDL_Rect window{};
			window.w = this->windowSurface->w;
			window.h = this->windowSurface->h;
			return window;
		}

		Position ScreenPositionCalculator::toWorldPosition(SDL_Rect screenPosition) {
			auto window = getWindowSize();
			return Position(
				screenPosition.x - window.w / 2,
				screenPosition.y - window.h / 2
			);
		}

	}
}