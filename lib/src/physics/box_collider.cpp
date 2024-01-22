#include <math.hpp>
#include <components.hpp>
#include <physics.hpp>

#include <utility>

namespace pong::physics {

	void BoxCollider::setPosition(world::Position position) {
		this->position = std::move(position);
	}
	
	world::Position BoxCollider::getPosition() const {
		return this->position;
	}
		
	void BoxCollider::setArea(math::Vector2D area) {
		this->area = area;
	}
		
	math::Vector2D BoxCollider::getArea() const {
		return this->area;
	}

	bool BoxCollider::intersects(const BoxCollider& collider) const {
		return std::max(this->position.x - this->area.x / 2, collider.position.x - collider.area.x / 2) 
		< std::min(this->position.x + this->area.x / 2, collider.position.x + collider.area.x / 2) 
		&& std::max(this->position.y + this->area.y / 2, collider.position.y + this->area.y / 2)
	 	> std::min(this->position.y - this->area.y / 2, collider.position.y - collider.area.y / 2);
	}
}
