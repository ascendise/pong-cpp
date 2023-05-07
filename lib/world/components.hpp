#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include "world.hpp"

namespace pong {
	namespace world {

		class Position : public Component {
		private:
			int x = 0;
			int y = 0;
		public:
			void setX(int x) { this->x = x; }
			int getX() { return this->x; }
			void setY(int y) { this->y = y; }
			int getY() { return this->y; }
		};

	}
}

#endif