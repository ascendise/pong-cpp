#include <iostream>
#include <memory>
#include <stdexcept>
#include <SDL.h>
#include <SDL_image.h>
#include <world.hpp>
#include <components.hpp>
#include <rendering.hpp>   
#include <physics.hpp>
#include <events.hpp>
#include <math.hpp>

using namespace pong::world;
using namespace pong::world::events;
using namespace pong::physics;
using namespace pong::rendering;
using namespace pong::math;

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
        //World + EventQueue
    EventQueue eventQueue;
    eventQueue.registerProcessor(std::make_unique<CollisionEventProcessor>());
    World world(std::make_unique<EventQueue>(std::move(eventQueue)));
        //Background
    std::vector<std::unique_ptr<Component>> backgroundComponents;
    backgroundComponents.push_back(std::make_unique<Position>(0, 0));
    auto texture = Texture::loadTexture(renderer, "../assets/Background.png");
    backgroundComponents.push_back(std::make_unique<Sprite>(std::move(texture), 1, 0));
    world.registerEntity(std::move(backgroundComponents));
        //Ball
    std::vector<std::unique_ptr<Component>> ballComponents;
    ballComponents.push_back(std::make_unique<Position>(0, 0));
    auto ballTexture = Texture::loadTexture(renderer, "../assets/anim_test.png");
    ballComponents.push_back(std::make_unique<Sprite>(std::move(ballTexture), 4, 0.1));
    RigidBody ballBody;
    ballBody.setBounce(1);
    ballBody.getVelocity().x = 250;
    ballBody.getVelocity().y = 250;
    ballComponents.push_back(std::make_unique<RigidBody>(std::move(ballBody)));
    ballComponents.push_back(std::make_unique<BoxCollider>(Position(0, 0), Vector2D(64, 64)));
    world.registerEntity(std::move(ballComponents));
        //Invisible Middle Wall (Vertical)
    std::vector<std::unique_ptr<Component>> wallComponents;
    wallComponents.push_back(std::make_unique<Position>(300, 0));
    RigidBody wallBody;
    wallBody.setBounce(1);
    wallBody.setVelocity(Vector2D(0, 0));
    wallComponents.push_back(std::make_unique<RigidBody>(std::move(wallBody)));
    wallComponents.push_back(std::make_unique<BoxCollider>(Position(300, 0), Vector2D(64, 64)));
    auto wallTexture = Texture::loadTexture(renderer, "../assets/wall.png");
    wallComponents.push_back(std::make_unique<Sprite>(std::move(wallTexture), 1, 0));
    world.registerEntity(std::move(wallComponents));
        //Systems
    world.registerSystem(std::make_unique<PhysicsSystem>(world.getClock()));
    world.registerSystem(std::make_unique<RenderingSystem>(renderer, world.getClock()));
    world.registerSystem(std::make_unique<CollisionSystem>(world.getEventQueue()));
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