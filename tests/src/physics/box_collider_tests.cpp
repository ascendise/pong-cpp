#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <physics.hpp>

using pong::physics::BoxCollider;

TEST(BoxColliderTests, Intersects_BothCollidersIntersect_ShouldReturnTrue) {
    //Arrange
    BoxCollider collider1(Position(0, 0), Vector2D(2, 2));
    BoxCollider collider2(Position(1, 1), Vector2D(2, 2));
    //Act
    bool res = collider1.intersects(collider2);
    //Assert
    EXPECT_TRUE(res);
}

TEST(BoxColliderTests, Intersects_CollidersDontIntersect_ShouldReturnFalse) {
    //Arrange
    BoxCollider collider1(Position(0, 0), Vector2D(1, 1));
    BoxCollider collider2(Position(5, 5), Vector2D(1, 1));
    //Act
    bool res = collider1.intersects(collider2);
    //Assert
    EXPECT_FALSE(res);
}