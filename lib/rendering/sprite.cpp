#include "rendering.hpp"
#include <stdexcept>

namespace pong {
	namespace rendering {

		Sprite::Sprite(std::shared_ptr<ITexture> texture, int spriteCount) {
			this->texture = texture;
			this->spriteCount = spriteCount;
			this->currentSprite = 0;
			this->sprites = getAnimationRects();
		}

		std::vector<SDL_Rect> Sprite::getAnimationRects() {
			SDL_Rect textureSize = texture->getTextureSize();
			auto rects = std::vector<SDL_Rect>();
			for (int i = 1; i <= this->spriteCount; i++) {
				SDL_Rect sprite{};
				sprite.w = textureSize.w  / this->spriteCount;
				sprite.h = textureSize.h;
				sprite.x = sprite.w * (i - 1);
				rects.push_back(sprite);
			}
			return rects;
		}


		const SDL_Rect Sprite::getNextRect() {
			auto& rect = this->sprites[this->currentSprite];
			this->currentSprite++;
			if (this->currentSprite >= this->spriteCount) {
				this->currentSprite = 0;
			}
			return rect;
		}

		std::shared_ptr<ITexture> Sprite::getTexture() {
			return this->texture;
		}

	}
}