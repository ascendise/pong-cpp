#include <rendering/utils.hpp>

namespace pong {
	namespace rendering {

		ScreenPositionCalculator::ScreenPositionCalculator(std::shared_ptr<ISurface> screenSurface) :
			screenSurface(screenSurface) {}
		
		SDL_Rect ScreenPositionCalculator::toScreenPosition(Position position) {
			auto window = screenSurface->getWindowSize();
			SDL_Rect screenPosition{};
			screenPosition.x = position.x + window.w / 2;
			screenPosition.y = position.y + window.h / 2;
			return screenPosition;
		}

		Position ScreenPositionCalculator::toWorldPosition(SDL_Rect screenPosition) {
			auto window = screenSurface->getWindowSize();
			return Position(
				screenPosition.x - window.w / 2,
				screenPosition.y - window.h / 2
			);
		}

	}
}