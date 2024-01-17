#include <rendering.hpp>

#include <SDL_image.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>

#include <string>

namespace pong::rendering {

	Texture Texture::loadTexture(SDL_Renderer* renderer, const std::string& path) {
		auto* surface = IMG_Load(path.c_str());
		auto* sdlTexture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		return Texture(sdlTexture);
	}

	SDL_Rect Texture::getTextureSize() const{
		SDL_Rect size = { 0, 0, 0, 0};
		SDL_QueryTexture(texture, nullptr, nullptr, &size.w, &size.h);
		return size;
	}

	Texture& Texture::operator=(Texture&& other) noexcept {
		if (this != &other) {
			this->texture = other.texture;
		}
		return *this;
	}

	Texture::~Texture() {
		SDL_DestroyTexture(this->texture);
	};
}