#include <iostream>
#include <memory>
#include <stdexcept>
#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
    auto window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    if(!window) {
        std::cerr << SDL_GetError();
        return -1;
    }
    auto rendererFlags = SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_TARGETTEXTURE;
    auto renderer = SDL_CreateRenderer(window, -1, rendererFlags);
    if(!renderer) {
        std::cerr << SDL_GetError();
        SDL_DestroyWindow(window);
        return -1;  
    }
    auto backgroundImg = IMG_Load("../assets/Background.png");
    auto backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundImg);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Event event;
    while(true) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)) {
        }
    }
    SDL_FreeSurface(backgroundImg);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}