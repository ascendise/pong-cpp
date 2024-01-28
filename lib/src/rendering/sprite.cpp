#include <rendering.hpp>

#include <chrono>
#include <memory>
#include <vector>


namespace pong::rendering {

	Sprite::Sprite(std::unique_ptr<ITexture>&& texture, int spriteCount, float duration) :
		spriteCount(spriteCount),
		texture(std::move(texture)),
		avgFrameTime(duration / (float)spriteCount), 
		sprites(this->getAnimationRects()) {
	
	}

	const std::vector<SDL_Rect> Sprite::getAnimationRects() {
		SDL_Rect const textureSize = texture->getTextureSize();
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
		const auto& rect = this->sprites[this->currentSprite];
		return rect;
	}

	bool Sprite::isPastFrameTime(
		std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> time
	) const {
		auto duration = time - lastUpdate;
		auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
		auto seconds = static_cast<float>(millis.count()) / 1000.0f; //MAYBE BUG?
		return seconds > this->avgFrameTime; 
	}

	std::unique_ptr<ITexture>& Sprite::getTexture() {
		return this->texture;
	}
}