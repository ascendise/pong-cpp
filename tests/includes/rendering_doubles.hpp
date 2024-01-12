#ifndef RENDERING_DOUBLES_HPP
#define RENDERING_DOUBLES_HPP

#include <SDL.h>
#include <rendering.hpp>
#include <rendering_utils.hpp>

using namespace pong::rendering;

class FakeSurface : public ISurface {
private:
	int width;
	int height;
public:
	FakeSurface(int width, int height) : width(width), height(height) {}
	SDL_Rect getWindowSize() {
		SDL_Rect window{};
		window.w = width;
		window.h = height;
		return window;
	}
};

class FakeTexture : public ITexture {
private:
    SDL_Rect size;
public:
    FakeTexture(SDL_Rect size) {
        this->size = size;
    }
    SDL_Texture* getSDLTexture() {
        return nullptr;
    };
    SDL_Rect getTextureSize() {
        return size;
    };
};

#endif