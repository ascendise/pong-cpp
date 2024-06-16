#include <components.hpp>
#include <math.hpp>
#include <physics.hpp>

#include <utility>

namespace pong::physics {

void BoxCollider::setPosition(world::Position position) { this->position = std::move(position); }

world::Position BoxCollider::getPosition() const { return this->position; }

void BoxCollider::setArea(math::Vector2D area) { this->area = area; }

math::Vector2D BoxCollider::getArea() const { return this->area; }

bool BoxCollider::intersects(const BoxCollider &collider) const {
  float thisLeftSide = this->position.x - this->area.x / 2.0f;
  float thisRightSide = this->position.x + this->area.x / 2.0f;
  float thisTop = this->position.y + this->area.y / 2.0f;
  float thisBottom = this->position.y - this->area.y / 2.0f;
  float colliderLeftSide = collider.position.x - collider.area.x / 2.0f;
  float colliderRightSide = collider.position.x + collider.area.x / 2.0f;
  float colliderTop = collider.position.y + collider.area.y / 2.0f;
  float colliderBottom = collider.position.y - collider.area.y / 2.0f;
  return std::max(thisLeftSide, colliderLeftSide) < std::min(thisRightSide, colliderRightSide) &&
         std::max(thisBottom, colliderBottom) < std::min(thisTop, colliderTop);
}

} // namespace pong::physics
