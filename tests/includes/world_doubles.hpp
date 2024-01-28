#ifndef WORLD_DOUBLES_HPP
#define WORLD_DOUBLES_HPP

#include <events.hpp>
#include <world.hpp>

namespace pong::world::testing {

class FakeComponent : public Component {
private:
  int value;

public:
  void setValue(int value) { this->value = value; };
  int getValue() const { return value; };
};

class FakeSystem : public System {
private:
  int value;

public:
  FakeSystem(int value) : value(value) {}
  void run(std::vector<Entity> &entities) override {
    for (auto &entity : entities) {
      auto &component = entity.getComponent<FakeComponent>().value().get(); // NOLINT bugprone-unchecked-optional-access
      component.setValue(value);
    }
  }
};

class StubEventQueue : public events::IEventQueue {
  void registerProcessor(std::unique_ptr<pong::world::events::EventProcessor> &&processor) override {}
  void enqueue(std::shared_ptr<pong::world::events::Event> &&event) override {}
  void processEvents() override {}
};

class ClockStub : public IReadOnlyClock {
private:
  float fixedTimeDelta;

public:
  ClockStub(float fixedTimeDelta) : fixedTimeDelta(fixedTimeDelta) {}
  float getFrameTimeDelta() const override { return fixedTimeDelta; };

  std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> now() const override {
    return std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds>();
  }
};
} // namespace pong::world::testing

#endif
