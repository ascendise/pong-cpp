#include "rendering.hpp"
#include <stdexcept>
#include <chrono>
#include <iostream>


namespace pong {
	namespace rendering {

		Sprite::Sprite(std::unique_ptr<ITexture>&& texture, int spriteCount, float duration) :
			texture(std::move(texture)),
			spriteCount(spriteCount),
			currentSprite(0)
		{
			this->sprites = getAnimationRects();
			this->avgFrameTime = duration / (float)spriteCount;
		}

		std::vector<SDL_Rect> Sprite::getAnimationRects() {
			SDL_Rect textureSize = texture->getTextureSize();
			std::vector<SDL_Rect> rects;
			for (int i = 1; i <= this->spriteCount; i++) {
				SDL_Rect sprite{};
				sprite.w = textureSize.w  / this->spriteCount;
				sprite.h = textureSize.h;
				sprite.x = sprite.w * (i - 1);
				rects.push_back(sprite);
			}
			return rects;
		}


		const SDL_Rect Sprite::getNextRect(
			std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> time
		) {
			if(isPastFrameTime(time)){
				this->currentSprite++;
				if (this->currentSprite >= this->spriteCount) {
					this->currentSprite = 0;
				}				
				lastUpdate = time;
			}
			auto& rect = this->sprites[this->currentSprite];
			return rect;
		}

		bool Sprite::isPastFrameTime(
			std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> time
		) {
			auto duration = time - lastUpdate;
			auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
			auto seconds = millis.count() / 1000.0;
			return seconds > this->avgFrameTime;
		}

		std::unique_ptr<ITexture>& Sprite::getTexture() {
			return this->texture;
		}

	}
}