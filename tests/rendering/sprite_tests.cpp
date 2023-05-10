#include <gtest/gtest.h>
#include <rendering/rendering.hpp>
#include "test_doubles/fakes/fake_texture.cpp"
#include <memory>

using pong::rendering::FakeTexture;
using pong::rendering::ITexture;
using pong::rendering::Sprite;

TEST(SpriteTests, GetNextRect_SingleImageRect_ShouldReturnCorrectSize) {
    //Arrange
    FakeTexture texture(SDL_Rect { .w = 64, .h = 64 });
    Sprite sut(std::make_shared<FakeTexture>(texture), 1);
    //Act
    auto rect1 = sut.getNextRect();
    auto rect2 = sut.getNextRect();
    //Assert
        //First Rect
    EXPECT_EQ(rect1.x, 0);
    EXPECT_EQ(rect1.y, 0);
    EXPECT_EQ(rect1.h, 64);
    EXPECT_EQ(rect1.w, 64);
        //Second Rect (Should be same)
    EXPECT_EQ(rect2.x, 0);
    EXPECT_EQ(rect2.y, 0);
    EXPECT_EQ(rect2.h, 64);
    EXPECT_EQ(rect2.w, 64);
}