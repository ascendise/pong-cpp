#include <iostream>
#include <memory>
#include <stdexcept>
#include <SDL.h>
#include <SDL_image.h>
#include <world/world.hpp>
#include <world/components.hpp>
#include <rendering/rendering.hpp>   
#include <physics/physics.hpp>

using pong::world::Component;
using pong::world::World;
using pong::world::Position;
using pong::rendering::Texture;
using pong::rendering::Sprite;
using pong::rendering::RenderingSystem;
using pong::physics::PhysicsSystem;
using pong::physics::RigidBody;

void runGameLoop(SDL_Renderer* renderer, World& world);

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
    World world;
        //Background
    std::vector<std::shared_ptr<Component>> backgroundComponents;
    backgroundComponents.push_back(std::make_shared<Position>(Position(0, 0)));
    auto texture = Texture::loadTexture(renderer, "../assets/Background.png");
    backgroundComponents.push_back(std::make_shared<Sprite>(Sprite(texture, 1, 0)));
    world.registerEntity(backgroundComponents);
        //Ball
    std::vector<std::shared_ptr<Component>> ballComponents;
    ballComponents.push_back(std::make_shared<Position>(Position(100, 100)));
    auto ballTexture = Texture::loadTexture(renderer, "../assets/anim_test.png");
    ballComponents.push_back(std::make_shared<Sprite>(Sprite(ballTexture, 4, 1)));
    RigidBody ballBody;
    ballBody.getVelocity()->x = 50;
    ballBody.getVelocity()->y = 50;
    ballComponents.push_back(std::make_shared<RigidBody>(std::move(ballBody)));
    world.registerEntity(ballComponents);
        //Systems
    world.registerSystem(std::make_unique<PhysicsSystem>(PhysicsSystem(world.getClock())));
    world.registerSystem(std::make_unique<RenderingSystem>(RenderingSystem(renderer)));
    runGameLoop(renderer, world);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}

void runGameLoop(SDL_Renderer* renderer, World& world) {
    SDL_Event event;
    while(true) {
        SDL_RenderClear(renderer);
        world.run();
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    return;
            }
        }
    }
}