#include <gtest/gtest.h>
#include <physics.hpp>

namespace pong::physics {

	TEST(BoxColliderTests, Intersects_BothCollidersIntersect_ShouldReturnTrue) {
	    //Arrange
	    BoxCollider const collider1(world::Position(0, 0), math::Vector2D(2, 2));
	    BoxCollider const collider2(world::Position(1, 1), math::Vector2D(2, 2));
	    //Act
	    bool const res = collider1.intersects(collider2);
	    //Assert
	    EXPECT_TRUE(res);
	}
	
	TEST(BoxColliderTests, Intersects_CollidersDontIntersect_ShouldReturnFalse) {
	    //Arrange
	    BoxCollider const collider1(world::Position(0, 0), math::Vector2D(1, 1));
	    BoxCollider const collider2(world::Position(5, 5), math::Vector2D(1, 1));
	    //Act
	    bool const res = collider1.intersects(collider2);
	    //Assert
	    EXPECT_FALSE(res);
	}
}
