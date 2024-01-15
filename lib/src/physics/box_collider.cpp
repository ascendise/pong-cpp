#include "physics.hpp"

namespace pong {
    namespace physics {

        world::Position& BoxCollider::getPosition() {
            return this->position;
        }

        math::Vector2D& BoxCollider::getArea() {
            return this->area;
        }

        bool BoxCollider::intersects(const BoxCollider& collider) {
            return std::max(this->position.x - this->area.x / 2, collider.position.x - collider.area.x / 2) 
                < std::min(this->position.x + this->area.x / 2, collider.position.x + collider.area.x / 2)
                && std::max(this->position.y + this->area.y / 2, collider.position.y + this->area.y / 2)
                > std::min(this->position.y - this->area.y / 2, collider.position.y - collider.area.y / 2);
        }
    }
}