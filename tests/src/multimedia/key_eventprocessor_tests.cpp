#include "multimedia.hpp"
#include "multimedia_doubles.hpp"
#include <gtest/gtest.h>

namespace pong::multimedia {

TEST(KeyEventProcessorTests, Process_ShouldPassEventToPlayerControl) {
  // Arrange
  std::vector<std::shared_ptr<world::Component>> components;
  SpyPlayerControl spyPlayerControl;
  std::vector<KeyEvent> *eventsSpy = spyPlayerControl.getKeyEventsSpy();
  components.push_back(std::make_shared<SpyPlayerControl>(spyPlayerControl));
  world::Entity entity(1L, components);
  KeyEventProcessor sut;
  SDL_KeyboardEvent sdlKeyEvent{};
  std::vector<std::reference_wrapper<IPlayerControl>> playerControls;
  playerControls.push_back(spyPlayerControl);
  // Act
  sut.process(KeyEvent(sdlKeyEvent, playerControls));
  // Assert
  ASSERT_EQ(1, eventsSpy->size()) << "Key event was not passed to key handler component";
}

} // namespace pong::multimedia
