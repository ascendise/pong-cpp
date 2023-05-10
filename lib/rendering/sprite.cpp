#include "rendering.hpp"
#include <stdexcept>

namespace pong {
	namespace rendering {

		Sprite::Sprite(std::shared_ptr<Texture> texture, int spriteCount) {
			this->texture = texture;
			this->spriteCount = spriteCount;
			this->currentSprite = 0;
			this->sprites = GetAnimationRects();
		}

		std::vector<SDL_Rect> Sprite::GetAnimationRects() {
			SDL_Rect textureSize = getTextureSize();
			auto rects = std::vector<SDL_Rect>();
			for (int i = 1; i <= this->spriteCount; i++) {
				SDL_Rect sprite{};
				sprite.w = textureSize.w * i;
				sprite.h = textureSize.h * i;
				sprite.x = textureSize.w * (i - 1);
				rects.push_back(sprite);
			}
			return rects;
		}

		SDL_Rect Sprite::getTextureSize() {
			SDL_Rect size = { 0, 0, 0, 0};
			SDL_QueryTexture(texture->GetTexture(), NULL, NULL, &size.w, &size.h);
			return size;
		}


		const SDL_Rect Sprite::GetNextRect() {
			auto rect = this->sprites[this->currentSprite];
			this->currentSprite++;
			if (this->currentSprite >= this->spriteCount) {
				this->currentSprite = 0;
			}
			return rect;
		}

		std::shared_ptr<Texture> Sprite::GetTexture() {
			return this->texture;
		}

	}
}