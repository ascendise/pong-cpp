#include "rendering.hpp"
#include <SDL_image.h>

namespace pong {
	namespace rendering {

		Texture& Texture::LoadTexture(SDL_Renderer* renderer, std::string path) {
			auto texture = Texture();
			auto surface = IMG_Load(path.c_str());
			texture.texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
			return texture;
		}
	}
}