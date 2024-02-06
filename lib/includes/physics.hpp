#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <components.hpp>
#include <math.hpp>
#include <rendering.hpp>
#include <world.hpp>

#include <utility>

namespace pong::physics {

/// @brief Responsible for updating the position of entities.
class MovementSystem : public world::System {
private:
  const world::IReadOnlyClock &clock;

public:
  MovementSystem(world::IReadOnlyClock &clock) : clock(clock) {}
  void run(std::vector<world::Entity> &entities) override;
};

/// @brief Component that enables physics for an entity
class RigidBody : public world::Component {
private:
  math::Vector2D velocity;
  float bounce = 1;

public:
  RigidBody() : velocity(math::Vector2D(0, 0)) {}
  RigidBody(math::Vector2D velocity, float bounce) : velocity(velocity), bounce(bounce) {}
  void setVelocity(math::Vector2D velocity);
  math::Vector2D getVelocity() const;
  void setBounce(float bounce);
  float getBounce() const;
};

/// @brief a recangular Collider used to define collision borders
class BoxCollider : public world::Component {
private:
  world::Position position;
  math::Vector2D area;

public:
  BoxCollider(world::Position position, math::Vector2D area) : position(std::move(position)), area(area) {}
  void setPosition(world::Position position);
  world::Position getPosition() const;
  void setArea(math::Vector2D area);
  math::Vector2D getArea() const;
  bool intersects(const BoxCollider &collider) const;
};

/// @brief Event emitted when a Collider intersects another collider
class CollisionEvent : public world::events::Event {
private:
  world::Entity &target;
  float angle;
  float bounce;

public:
  CollisionEvent(world::Entity &target, float angle, float bounce) : target(target), angle(angle), bounce(bounce) {}
  world::Entity &getTarget() const;

  /// @returns the collision angle in degrees
  float getAngle() const;

  /// @returns how bouncy the surface is the target hit.
  /// @n 1 -> bouncy; target returns with full speed
  /// @n 0.5 -> target returns with half speed
  /// @n 0 -> target velocity reduced to zero
  float getBounce() const;
};

/// @brief responsible for handling CollisionEvent. Calculates new velocity based on collision data
class CollisionEventProcessor : public world::events::EventProcessor {
private:
  math::Vector2D calculateVelocityAfterCollision(float angle, const RigidBody &targetRigidBody, float bounce);

public:
  void process(const world::events::Event &event) override;
};

/// @brief simple tuple of two Entities that collided with eachother.
struct Collision {
  world::Entity &entity1; // NOLINT misc-non-private-member-variables-in-classes
  world::Entity &entity2; // NOLINT misc-non-private-member-variables-in-classes
  Collision(world::Entity &entity1, world::Entity &entity2) : entity1(entity1), entity2(entity2) {}
};

/// @brief System responsible for detecting collisions between Entities
class CollisionSystem : public world::System {
private:
  world::events::IEventQueuePort &eventQueue;
  std::vector<Collision> findCollisions(std::vector<world::Entity> &entities);
  void pushCollisionEvent(world::Entity &target, world::Entity &hurdle);

public:
  CollisionSystem(world::events::IEventQueuePort &eventQueue) : eventQueue(eventQueue) {}
  void run(std::vector<world::Entity> &entities) override;
};

} // namespace pong::physics

#endif
