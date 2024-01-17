#ifndef RENDERING_DOUBLES_HPP
#define RENDERING_DOUBLES_HPP

#include <SDL.h>
#include <rendering.hpp>

namespace pong {
    namespace rendering {
        namespace testing {

            class FakeTexture : public ITexture {
            private:
                SDL_Rect size;
            public:
                FakeTexture(SDL_Rect size) {
                    this->size = size;
                }
                SDL_Texture* getSDLTexture() {
                    return nullptr;
                }
                SDL_Rect getTextureSize() const override {
                    return size;
                }
            };
        }
    }
}

#endif