#include "rendering.hpp"

namespace pong {
	namespace rendering {

		Sprite::Sprite(std::shared_ptr<Texture> texture, int spriteCount) {
			this->texture = texture;
			this->spriteCount = spriteCount;
			this->currentSprite = 0;
			this->sprites = GetAnimationRects();
		}

		std::vector<SDL_Rect> Sprite::GetAnimationRects() {
			SDL_Rect textureSize = { 0, 0, 0, 0 };
			SDL_QueryTexture(this->texture.get()->GetTexture(), NULL, NULL, &textureSize.w, &textureSize.h);
			auto rects = std::vector<SDL_Rect>();
			for (int i = 1; i <= this->spriteCount; i++) {
				SDL_Rect sprite{};
				sprite.w = textureSize.w * i;
				sprite.h = textureSize.h * i;
				sprite.x = textureSize.w * i - 1;
				rects.push_back(sprite);
			}
			return rects;
		}


		const SDL_Rect* Sprite::GetNextRect() {
			auto rect = this->sprites[this->currentSprite];
			this->currentSprite++;
			if (this->currentSprite == this->spriteCount) {
				this->currentSprite++;
			}
			return &rect;
		}

		std::shared_ptr<Texture> Sprite::GetTexture() {
			return this->texture;
		}

	}
}