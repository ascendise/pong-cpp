#include "multimedia.hpp"
#include "multimedia_doubles.hpp"
#include <gtest/gtest.h>

namespace pong::multimedia {

TEST(SystemEventProcessorTests, ReceivesQuitEvent_ShouldExitApplication) {
  // Arrange
  auto spySystemControl = std::make_unique<SpySystemControl>();
  int *exitCountSpy = spySystemControl->getExitCountSpy();
  SystemEventProcessor sut(std::move(spySystemControl));
  QuitAppEvent quitEvent;
  // Act
  sut.process(quitEvent);
  // Assert
  ASSERT_EQ(1, *exitCountSpy) << "System was not exited on event";
}

} // namespace pong::multimedia
