#include <world/world.hpp>

#ifndef FAKE_COMPONENT_CPP
#define FAKE_COMPONENT_CPP

class FakeComponent : public pong::world::Component {
private:
    int value;
public:
    void setValue(int value) { this->value = value; };
    int getValue() { return value; };
};

#endif