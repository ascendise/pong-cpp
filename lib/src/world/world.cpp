#include "world.hpp"

#include <stdexcept>
#include <algorithm>
#include <iostream>

namespace pong {
    namespace world {

        World::World(std::unique_ptr<events::IEventQueue>&& eventQueue)
            : eventQueue(std::move(eventQueue)), clock(std::make_unique<Clock>()) {
            this->clock->start();
        }

        void World::registerEntity(std::vector<std::unique_ptr<Component>>&& components) {
            Entity entity(this->idCounter++, std::move(components));
            this->entities.push_back(std::move(entity));
        }

        void World::removeEntity(long entityId) {
            auto has_id = [entityId](Entity& e) { return e.getId() == entityId; };
            auto remove_if_has_id = std::remove_if(this->entities.begin(), this->entities.end(), has_id);
            this->entities.erase(remove_if_has_id, this->entities.end());
        }

        std::optional<std::reference_wrapper<Entity>> World::findEntity(long entityId) {
            auto has_id = [entityId](Entity& e) { return e.getId() == entityId; };
            auto entity_iterator = std::find_if(this->entities.begin(), this->entities.end(), has_id);
            if (entity_iterator != this->entities.end()) {
                return std::ref(*entity_iterator);
            } else {
                return {};
            }
        }

        void World::registerSystem(std::unique_ptr<System>&& system) {
            this->systems.push_back(std::move(system));
        }

        void World::run() {
            for (auto& system : this->systems) {
                system->run(this->entities);
            }
            this->eventQueue->processEvents();
            clock->nextFrame();
        }

        IReadOnlyClock& World::getClock() {   
            return *this->clock;
        }

        events::IEventQueuePort& World::getEventQueue() {
            return *this->eventQueue;
        }
    }
}