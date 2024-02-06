#ifndef WORLD_HPP
#define WORLD_HPP

#include <events.hpp>

#include <algorithm>
#include <chrono>
#include <memory>
#include <optional>
#include <type_traits>
#include <vector>

namespace pong::world {

/// @brief Base Component that holds a specific chunk of data used by Systems
/// @n Component is meant to be inherited from and extended with data that is used by a System.
/// @n Example: A System that requires the X and Y coordinate of an entity, might look for a Component
/// that contains those coordinates.
class Component {
public:
  virtual ~Component() = default;
};

class Entity {
private:
  long id;
  std::vector<std::unique_ptr<Component>> components;
  void moveComponents(std::vector<std::unique_ptr<Component>> &&components) noexcept;

public:
  Entity(long id, std::vector<std::unique_ptr<Component>> &&components) : id(id), components(std::move(components)) {}
  Entity(const Entity &) = delete;
  Entity(Entity &&) noexcept;
  Entity &operator=(const Entity &) = delete;
  Entity &operator=(Entity &&) noexcept;
  long getId() const noexcept;
  /// @brief Searches for a Component of type T inside the Entity.
  /// @returns an optional that contains the found component if it exists or else nothing
  template <class T> std::optional<std::reference_wrapper<T>> getComponent() const {
    for (const auto &component : this->components) {
      try {
        auto &derived = dynamic_cast<T &>(*component);
        return std::ref(derived);
      } catch (std::bad_cast &) {
        // Try next component
      }
    }
    return {};
  }
  ~Entity() = default;
};

/// @brief System for interacting with the World
/// @n A System reads and manipulates Entity data. It might also interact through some of the Worlds exposed
/// @n interfaces to do things like read frame timings or queue events.
class System {
public:
  /// @brief runs through all entites and acts on the relevant components
  /// @param entities a collection of all entities in the world.
  virtual void run(std::vector<Entity> &entities) = 0;
  virtual ~System() = default;
};

class IReadOnlyClock {
public:
  virtual float getFrameTimeDelta() const = 0;
  virtual std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> now() const = 0;
  virtual ~IReadOnlyClock() = default;
};

/// A clock with it's main purposes being tracking the time between frames. This data is useful, as it can be used
/// in calculations whichs result may vary when frames are calculated faster.
/// @n Example: An Entity has a velocity and a position as vector. Every frame calculation, the velocity is added to
/// the position, moving the Entity. But computers have different performance, and some are able to calculate 60 frames
/// per second (FPS), while others are able to calculate 240+ FPS So the position after one second would be position +
/// FPS * velocity. To mitigate this, one can use the FrameTimeDelta in the formula (position + FPS * velocity *
/// __FrameTimeDelta__) and thus have a constant velocity on different hardware.
class Clock : public IReadOnlyClock {
private:
  std::chrono::high_resolution_clock clock;
  std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> timeLastFrame;
  float timeDiffNano;

public:
  /// @returns the time difference between nextFrame() calls.
  float getFrameTimeDelta() const override;
  std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> now() const override;

  /// starts the clock and time tracking
  void start();

  /// sets a point when the last frame is finished and the next frame is calculated.
  void nextFrame();
};

/// The framework around the ECS engine. Combines the systems, entites, components and event handling and orchestrates
/// the interaction between all the different parts of the engine.
class World {
private:
  long idCounter = 0;
  std::vector<Entity> entities;
  std::vector<std::unique_ptr<System>> systems;
  std::unique_ptr<events::IEventQueue> eventQueue;
  std::unique_ptr<Clock> clock;

public:
  World(std::unique_ptr<events::IEventQueue> &&eventQueue);

  /// @brief Creates a new entity inside the world with the passed components
  void registerEntity(std::vector<std::unique_ptr<Component>> &&components);

  void removeEntity(long entityId);
  std::optional<std::reference_wrapper<Entity>> findEntity(long entityId);

  /// @brief Registers a new system and appends it to the collection of systems.
  void registerSystem(std::unique_ptr<System> &&system);

  /// @brief Returns a write-only interface for enqueuing events.
  /// @n Example: Might be injected into events to enqueue events
  events::IEventQueuePort &getEventQueue();

  /// @brief Returns a read-only clock to get frame time information
  IReadOnlyClock &getClock() const;

  /// @brief Starts the game loop
  /// The list of registered entities gets passed to each system in order of registration. After all systems were run,
  /// the events get processed. After that, the game loop starts again.
  void run();
};
} // namespace pong::world

#endif
