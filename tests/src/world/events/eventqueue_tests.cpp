#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <event_doubles.hpp>

using pong::world::events::EventQueue;

TEST(EventQueueTests, ProcessEvents_ProcessorRegistered_ShouldSendEventToCorrectProcessor) {
    //Arrange
    EventQueue queue;
    queue.registerProcessor(std::make_unique<FakeEventProcessor>());
    //Act
    int processCount = 0;
    queue.enqueue(std::make_shared<FakeEvent>(&processCount));
    queue.processEvents();
    //Assert
    EXPECT_EQ(processCount, 1) << "Event has not been processed";
}

TEST(EventQueueTests, ProcessEvents_ProcessorRegistered_ShouldSendEventToAllProcessors) {
    //Arrange
    EventQueue queue;
    queue.registerProcessor(std::make_unique<FakeEventProcessor>());
    queue.registerProcessor(std::make_unique<FakeEventProcessor>());
    int processCount = 0;
    queue.enqueue(std::make_shared<FakeEvent>(&processCount));
    //Act
    queue.processEvents();
    //Assert
    ASSERT_EQ(processCount, 2) << "Event has not been processed by all registered EventProcessors";
}