#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "fake_event.cpp"
#include "fake_eventprocessor.cpp"

using pong::world::events::EventQueue;

TEST(EventQueueTests, ProcessEvents_ProcessorRegistered_ShouldSendEventToCorrectProcessor) {
    //Arrange
    EventQueue queue;
    queue.registerProcessor(std::make_unique<FakeEventProcessor>(FakeEventProcessor()));
    auto event = std::make_shared<FakeEvent>(FakeEvent());
    queue.enqueue(event);
    //Act
    queue.processEvents();
    //Assert
    ASSERT_TRUE(event->isProcessed());
}

TEST(EventQueueTests, ProcessEvents_ProcessorRegistered_ShouldSendEventToAllProcessors) {
    //Arrange
    EventQueue queue;
    queue.registerProcessor(std::make_unique<FakeEventProcessor>(FakeEventProcessor()));
    queue.registerProcessor(std::make_unique<FakeEventProcessor>(FakeEventProcessor()));
    auto event = std::make_shared<FakeEvent>(FakeEvent());
    queue.enqueue(event);
    //Act
    queue.processEvents();
    //Assert
    ASSERT_EQ(event->getProcessCount(), 2);
}