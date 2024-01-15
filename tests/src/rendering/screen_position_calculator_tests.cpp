#include <gtest/gtest.h>
#include <rendering_utils.hpp>
#include <rendering_doubles.hpp>

using namespace pong::rendering;

SDL_Surface createSurface(int w, int h) {
	SDL_Surface surface;
	surface.w = w;
	surface.h = h;
	return surface;
}

TEST(ScreenPositionCalculatorTests, toScreenPosition_middle_shouldReturnCorrectPosition) {
	//Arrange
	SDL_Surface window = createSurface(1280, 720);
	ScreenPositionCalculator sut(&window);
	//Act
	auto middle = Position(0, 0);
	auto screenPosition = sut.toScreenPosition(middle);
	//Assert
	EXPECT_EQ(screenPosition.x, 640);
	EXPECT_EQ(screenPosition.y, 360);
}

TEST(ScreenPositionCalculatorTests, toScreenPosition_offset_shouldReturnCorrectPosition) {
	//Arrange
	SDL_Surface window = createSurface(1280, 720);
	ScreenPositionCalculator sut(&window);
	//Act
	auto position = Position(-15, 200);
	auto screenPosition = sut.toScreenPosition(position);
	//Assert
	EXPECT_EQ(screenPosition.x, 625);
	EXPECT_EQ(screenPosition.y, 560);
}

TEST(ScreenPositionCalculatorTests, toWorldPosition_middle_shouldReturnCorrectPosition) {
	//Arrange
	SDL_Surface window = createSurface(1280, 720);
	ScreenPositionCalculator sut(&window);
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
	SDL_Surface window = createSurface(1280, 720);
	ScreenPositionCalculator sut(&window);
	//Act
	SDL_Rect position;
	position.x = 625;
	position.y = 560;
	auto worldPosition = sut.toWorldPosition(position);
	//Assert
	EXPECT_EQ(worldPosition.x, -15);
	EXPECT_EQ(worldPosition.y, 200);
}