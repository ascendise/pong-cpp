#include "physics.hpp"

namespace pong {
    namespace physics {

        BoxCollider::BoxCollider(Position position, Vector2D area) {
            this->position = std::make_unique<Position>(position);
            this->area = std::make_unique<Vector2D>(area);
        }

        Position BoxCollider::getPosition() {
            return *this->position;
        }

        Vector2D BoxCollider::getArea() {
            return *this->area;
        }

        bool BoxCollider::intersects(const BoxCollider& collider) {
            return std::max(this->position->x, collider.position->x) < std::min(this->position->x + this->area->x, collider.position->x + collider.area->x)
                && std::max(this->position->y, collider.position->y) < std::min(this->position->y + this->area->y, collider.position->y + collider.area->y);
        }
    }
}