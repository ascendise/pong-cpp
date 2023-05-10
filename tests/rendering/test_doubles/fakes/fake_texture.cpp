#ifndef FAKE_TEXTURE_CPP
#define FAKE_TEXTURE_CPP

#include <rendering/rendering.hpp>

namespace pong {
    namespace rendering {
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
    }
}

#endif