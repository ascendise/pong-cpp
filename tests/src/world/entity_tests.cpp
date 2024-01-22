#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include <world.hpp>
#include <world_doubles.hpp>

namespace pong::world {

	TEST(EntityTests, GetComponent_ComponentExists_ShouldReturnComponent) {
	    //Arrange
	    auto component = testing::FakeComponent();
	    auto components = std::vector<std::unique_ptr<Component>>();
	    components.push_back(std::make_unique<testing::FakeComponent>());
	    Entity sut(1, std::move(components));
	    //Act
	    auto foundComponent = sut.getComponent<testing::FakeComponent>();
	    //Assert
	    ASSERT_TRUE(foundComponent.has_value());
	}
	
	TEST(EntityTests, GetComponent_ComponentDoesNotExist_ShouldReturnNullPtr) {
	    //Arrange
	    auto components = std::vector<std::unique_ptr<Component>>();
	    Entity sut(1, std::move(components));
	    //Act
	    auto foundComponent = sut.getComponent<testing::FakeComponent>();
	    //Assert
	    ASSERT_FALSE(foundComponent.has_value());
	}
	
	TEST(EntityTests, GetComponent_MultipleComponents_ShouldReturnCorrectComponent) {
	    //Arrange
	    class FakeComponent2 : public Component {
	    public:
	        int id2 = 2;
	    };
	    class FakeComponent3 : public Component {
	    public:
	        int id3 = 3;
	    };
	    auto components = std::vector<std::unique_ptr<Component>>();
	    components.push_back(std::make_unique<testing::FakeComponent>());
	    components.push_back(std::make_unique<FakeComponent2>());
	    components.push_back(std::make_unique<FakeComponent3>());
	    Entity sut(1, std::move(components));
	    //Act
	    auto foundComponent = sut.getComponent<FakeComponent3>();
	    //Assert
	    ASSERT_TRUE(foundComponent.has_value());
	}
}
