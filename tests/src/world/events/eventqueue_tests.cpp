#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <event_doubles.hpp>

using pong::world::events::EventQueue;

TEST(EventQueueTests, ProcessEvents_ProcessorRegistered_ShouldSendEventToCorrectProcessor) {
    //Arrange
    EventQueue queue;
    queue.registerProcessor(std::make_unique<FakeEventProcessor>());
    //Act
    FakeEvent fakeEvent;
    int* fakeEventCountSpy = fakeEvent.spyOnProcessCount();
    queue.enqueue(std::move(fakeEvent));
    queue.processEvents();
    //Assert
    EXPECT_EQ(*fakeEventCountSpy, 1) << "Event has not been processed";
}

TEST(EventQueueTests, ProcessEvents_ProcessorRegistered_ShouldSendEventToAllProcessors) {
    //Arrange
    EventQueue queue;
    queue.registerProcessor(std::make_unique<FakeEventProcessor>());
    queue.registerProcessor(std::make_unique<FakeEventProcessor>());
    FakeEvent event;
    int* fakeEventCountSpy = event.spyOnProcessCount();
    queue.enqueue(std::move(event));
    //Act
    queue.processEvents();
    //Assert
    ASSERT_EQ(*fakeEventCountSpy, 2) << "Event has not been processed by all registered EventProcessors";
}