#include "rendering.hpp"
#include <SDL_image.h>

namespace pong {
	namespace rendering {

		std::unique_ptr<Texture> Texture::loadTexture(SDL_Renderer* renderer, std::string path) {
			auto texture = std::make_unique<Texture>(Texture());
			auto surface = IMG_Load(path.c_str());
			texture->texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
			return texture;
		}

		SDL_Rect Texture::getTextureSize() {
			SDL_Rect size = { 0, 0, 0, 0};
			SDL_QueryTexture(texture, NULL, NULL, &size.w, &size.h);
			return size;
		}

		Texture::Texture(const Texture&& other) noexcept { 
                this->texture = other.texture; 
            }
		Texture& Texture::operator=(const Texture&& other) noexcept {
			if (this != &other) {
				this->texture = other.texture;
			}
			return *this;
		}
		Texture::~Texture() {
			SDL_DestroyTexture(this->texture);
		};
	}
}