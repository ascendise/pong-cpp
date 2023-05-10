#include <gtest/gtest.h>
#include <rendering/rendering.hpp>
#include "test_doubles/fakes/fake_texture.cpp"
#include <memory>

using pong::rendering::FakeTexture;
using pong::rendering::ITexture;
using pong::rendering::Sprite;

TEST(SpriteTests, GetNextRect_SingleImageRect_ShouldReturnCorrectSize) {
    //Arrange
    SDL_Rect size{};
    size.w = 64;
    size.h = 64;
    Sprite sut(std::make_shared<FakeTexture>(FakeTexture(size)), 1);
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

TEST(SpriteTests, GetNextRect_SpriteSheet_ShouldReturnCorrectSizes) {
    //Arrange
    SDL_Rect size{};
    size.w = 300;
    size.h = 50;
    Sprite sut(std::make_shared<FakeTexture>(FakeTexture(size)), 3);
    //Act
    auto rect1 = sut.getNextRect();
    auto rect2 = sut.getNextRect();
    auto rect3 = sut.getNextRect();
    //Assert
        //First Rect
    EXPECT_EQ(rect1.x, 0);
    EXPECT_EQ(rect1.y, 0);
    EXPECT_EQ(rect1.h, 50);
    EXPECT_EQ(rect1.w, 100);
        //Second Rect
    EXPECT_EQ(rect2.x, 100);
    EXPECT_EQ(rect2.y, 0);
    EXPECT_EQ(rect2.h, 50);
    EXPECT_EQ(rect2.w, 100);
        //Third Rect
    EXPECT_EQ(rect3.x, 200);
    EXPECT_EQ(rect3.y, 0);
    EXPECT_EQ(rect3.h, 50);
    EXPECT_EQ(rect3.w, 100);
}

TEST(SpriteTests, GetNextRec_LoopThroughSpriteSheet_ShouldStartAtBeginningAgain) {
    //Arrange
    SDL_Rect size = { };
    size.h = 50;
    size.w = 200;
    Sprite sut(std::make_shared<FakeTexture>(FakeTexture(size)), 2);
    //Act
    sut.getNextRect();
    sut.getNextRect();
    auto rect = sut.getNextRect();
    //Assert
    EXPECT_EQ(rect.x, 0);
    EXPECT_EQ(rect.y, 0);
    EXPECT_EQ(rect.h, 50);
    EXPECT_EQ(rect.w, 100);
}