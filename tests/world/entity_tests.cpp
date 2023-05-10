#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include <world/world.hpp>
#include "test_doubles/fakes/fake_component.cpp"

using ::testing::Eq;
using namespace pong::world;

TEST(EntityTests, GetComponent_ComponentExists_ShouldReturnComponent) {
    //Arrange
    auto component = FakeComponent();
    auto components = std::vector<std::shared_ptr<Component>> { 
        std::make_shared<FakeComponent>(component) 
    };
    auto sut = Entity(1, components);
    //Act
    auto foundComponent = sut.getComponent<FakeComponent>();
    //Assert
    ASSERT_NE(foundComponent.get(), nullptr);
}

TEST(EntityTests, GetComponent_ComponentDoesNotExist_ShouldReturnNullPtr) {
    //Arrange
    auto components = std::vector<std::shared_ptr<Component>>();
    auto sut = Entity(1, components);
    //Act
    auto foundComponent = sut.getComponent<FakeComponent>();
    //Assert
    ASSERT_EQ(foundComponent.get(), nullptr);
}