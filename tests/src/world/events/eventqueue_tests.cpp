#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <event_doubles.hpp>

namespace pong::world::events {

	TEST(EventQueueTests, ProcessEvents_ProcessorRegistered_ShouldSendEventToCorrectProcessor) {
	    //Arrange
	    EventQueue queue;
	    queue.registerProcessor(std::make_unique<testing::FakeEventProcessor>());
	    //Act
	    int processCount = 0;
	    queue.enqueue(std::make_shared<testing::FakeEvent>(&processCount));
	    queue.processEvents();
	    //Assert
	    EXPECT_EQ(processCount, 1) << "Event has not been processed";
	}
	
	TEST(EventQueueTests, ProcessEvents_ProcessorRegistered_ShouldSendEventToAllProcessors) {
	    //Arrange
	    EventQueue queue;
	    queue.registerProcessor(std::make_unique<testing::FakeEventProcessor>());
	    queue.registerProcessor(std::make_unique<testing::FakeEventProcessor>());
	    int processCount = 0;
	    queue.enqueue(std::make_shared<testing::FakeEvent>(&processCount));
	    //Act
	    queue.processEvents();
	    //Assert
	    ASSERT_EQ(processCount, 2) << "Event has not been processed by all registered EventProcessors";
	}
}
