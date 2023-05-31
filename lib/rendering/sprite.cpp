#include "rendering.hpp"
#include <stdexcept>
#include <chrono>
#include <iostream>

using std::chrono::milliseconds;

namespace pong {
	namespace rendering {

		Sprite::Sprite(std::shared_ptr<ITexture> texture, int spriteCount, float duration) {
			this->texture = texture;
			this->spriteCount = spriteCount;
			this->currentSprite = 0;
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


		const SDL_Rect Sprite::getNextRect(time_point<high_resolution_clock, nanoseconds> time) {
			auto& rect = this->sprites[this->currentSprite];
			if(isPastFrameTime(time)){
				this->currentSprite++;
				if (this->currentSprite >= this->spriteCount) {
					this->currentSprite = 0;
				}				
				lastUpdate = time;
			}
			return rect;
		}

		bool Sprite::isPastFrameTime(time_point<high_resolution_clock, nanoseconds> time) {
			auto duration = time - lastUpdate;
			auto millis = std::chrono::duration_cast<milliseconds>(duration);
			auto seconds = millis.count() / 1000.0;
			return seconds > this->avgFrameTime;
		}

		std::shared_ptr<ITexture> Sprite::getTexture() {
			return this->texture;
		}

	}
}