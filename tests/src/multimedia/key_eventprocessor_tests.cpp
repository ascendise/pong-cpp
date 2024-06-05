#include "multimedia.hpp"
#include "multimedia_doubles.hpp"
#include <gtest/gtest.h>

namespace pong::multimedia {

TEST(KeyEventProcessorTests, Process_ShouldPassEventToPlayerControl) {
  // Arrange
  std::vector<world::Entity> entities;
  std::vector<std::unique_ptr<world::Component>> components;
  SpyPlayerControl spyPlayerControl;
  std::vector<KeyEvent> *eventsSpy = spyPlayerControl.getKeyEventsSpy();
  components.push_back(std::make_unique<SpyPlayerControl>(std::move(spyPlayerControl)));
  world::Entity entity(1L, std::move(components));
  entities.push_back(std::move(entity));
  KeyEventProcessor sut(entities);
  SDL_KeyboardEvent sdlKeyEvent{};
  // Act
  sut.process(KeyEvent(sdlKeyEvent));
  // Assert
  ASSERT_EQ(1, eventsSpy->size()) << "Key event was not passed to key handler component";
}

} // namespace pong::multimedia
