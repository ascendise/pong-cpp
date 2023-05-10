#include "rendering.hpp"
#include <SDL_image.h>

namespace pong {
	namespace rendering {

		std::shared_ptr<Texture> Texture::LoadTexture(SDL_Renderer* renderer, std::string path) {
			auto texture = std::make_shared<Texture>(Texture());
			auto surface = IMG_Load(path.c_str());
			texture->texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
			return texture;
		}
	}
}