#include <gtest/gtest.h>
#include <rendering.hpp>
#include <rendering_doubles.hpp>
#include <memory>

using pong::rendering::ITexture;
using pong::rendering::Sprite;

TEST(SpriteTests, GetNextRect_SingleImageRect_ShouldReturnCorrectSize) {
    //Arrange
    SDL_Rect size{};
    size.w = 64;
    size.h = 64;
    Sprite sut(std::make_shared<FakeTexture>(FakeTexture(size)), 1, 0);
    //Act
    auto rect1 = sut.getNextRect(time_point<high_resolution_clock, nanoseconds>());
    auto rect2 = sut.getNextRect(time_point<high_resolution_clock, nanoseconds>());
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
    Sprite sut(std::make_shared<FakeTexture>(FakeTexture(size)), 3, 2);
    std:tm time {
        0,
        0,
        12,
        1,
        1,
        2000,
        6,
        0,
     };
    //Act
    auto rect1 = sut.getNextRect(std::chrono::high_resolution_clock::from_time_t(std::mktime(&time)));
    time.tm_sec = 1;
    auto rect2 = sut.getNextRect(std::chrono::high_resolution_clock::from_time_t(std::mktime(&time)));
    time.tm_sec = 2;
    auto rect3 = sut.getNextRect(std::chrono::high_resolution_clock::from_time_t(std::mktime(&time)));
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
    Sprite sut(std::make_shared<FakeTexture>(FakeTexture(size)), 2, 0);
    //Act
    sut.getNextRect(time_point<high_resolution_clock, nanoseconds>());
    sut.getNextRect(time_point<high_resolution_clock, nanoseconds>());
    auto rect = sut.getNextRect(time_point<high_resolution_clock, nanoseconds>());
    //Assert
    EXPECT_EQ(rect.x, 0);
    EXPECT_EQ(rect.y, 0);
    EXPECT_EQ(rect.h, 50);
    EXPECT_EQ(rect.w, 100);
}