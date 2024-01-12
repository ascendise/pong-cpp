#ifndef WORLD_DOUBLES_HPP
#define WORLD_DOUBLES_HPP

#include <world.hpp>
#include <events.hpp>	

using namespace pong::world;
using namespace pong::world::events;


class FakeComponent : public pong::world::Component {
private:
    int value;
public:
    void setValue(int value) { this->value = value; };
    int getValue() const { return value; };
};

class FakeSystem : public pong::world::System {
private:
    int value;
public:
    FakeSystem(int value) { this->value = value; };
    void run(std::vector<std::shared_ptr<pong::world::Entity>> entities) {
        for (auto& entity : entities) {
            auto component = entity.get()->getComponent<FakeComponent>();
            component.get()->setValue(value);
        }
    }
};

class StubEventQueue : public IEventQueue {
    void registerProcessor(std::unique_ptr<EventProcessor> processor) { }
    void enqueue(std::shared_ptr<Event> event) { }
    void processEvents() { }
};

class ClockStub : public IReadOnlyClock {
private:
    float fixedTimeDelta;
public:
    ClockStub(float fixedTimeDelta) {
        this->fixedTimeDelta = fixedTimeDelta;
    }
    float getFrameTimeDelta() {
        return fixedTimeDelta;
    };

    time_point<high_resolution_clock, nanoseconds> now() {
        return time_point<high_resolution_clock, nanoseconds>();
    }
};

#endif