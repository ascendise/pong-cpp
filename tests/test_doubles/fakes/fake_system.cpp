#include <world/world.hpp>
#include "./fake_component.cpp"

#ifndef FAKE_SYSTEM_CPP
#define FAKE_SYSTEM_CPP

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

#endif