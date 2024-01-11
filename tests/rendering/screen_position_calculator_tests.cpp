#include <gtest/gtest.h>
#include <rendering/utils.hpp>
#include "test_doubles/fakes/fake_surface.cpp"

using namespace pong::rendering;

TEST(ScreenPositionCalculatorTests, toScreenPosition_middle_shouldReturnCorrectPosition) {
	//Arrange
	ScreenPositionCalculator sut(std::make_shared<FakeSurface>(1280, 720));
	//Act
	auto middle = Position(0, 0);
	auto screenPosition = sut.toScreenPosition(middle);
	//Assert
	EXPECT_EQ(screenPosition.x, 640);
	EXPECT_EQ(screenPosition.y, 360);
}

TEST(ScreenPositionCalculatorTests, toScreenPosition_offset_shouldReturnCorrectPosition) {
	//Arrange
	ScreenPositionCalculator sut(std::make_shared<FakeSurface>(1280, 720));
	//Act
	auto position = Position(-15, 200);
	auto screenPosition = sut.toScreenPosition(position);
	//Assert
	EXPECT_EQ(screenPosition.x, 625);
	EXPECT_EQ(screenPosition.y, 560);
}

TEST(ScreenPositionCalculatorTests, toWorldPosition_middle_shouldReturnCorrectPosition) {
	//Arrange
	ScreenPositionCalculator sut(std::make_shared<FakeSurface>(1280, 720));
	//Act
	SDL_Rect middle;
	middle.x = 640;
	middle.y = 360;
	auto worldPosition = sut.toWorldPosition(middle);
	//Assert
	EXPECT_EQ(worldPosition.x, 0);
	EXPECT_EQ(worldPosition.y, 0);
}

TEST(ScreenPositionCalculatorTests, toWorldPosition_offset_shouldReturnCorrectPosition) {
	//Arrange
	ScreenPositionCalculator sut(std::make_shared<FakeSurface>(1280, 720));
	//Act
	SDL_Rect position;
	position.x = 625;
	position.y = 560;
	auto worldPosition = sut.toWorldPosition(position);
	//Assert
	EXPECT_EQ(worldPosition.x, -15);
	EXPECT_EQ(worldPosition.y, 200);
}