#ifndef MULTIMEDIA_DOUBLES_HPP
#define MULTIMEDIA_DOUBLES_HPP

#include "multimedia.hpp"
#include <vector>

namespace pong::multimedia {

class SpySystemControl : public ISystemControl {

private:
  int exitCount = 0;

public:
  void exit() override { exitCount++; }

  int *getExitCountSpy() { return &exitCount; }
};

class SpyPlayerControl : public IPlayerControl {
private:
  std::vector<KeyEvent> *caughtKeyEvents;

public:
  SpyPlayerControl() : caughtKeyEvents(new std::vector<KeyEvent>()) {}
  std::vector<KeyEvent> *getKeyEventsSpy() { return caughtKeyEvents; }
  void handleKeyEvent(const KeyEvent &keyEvent) override { caughtKeyEvents->push_back(keyEvent); }
};

} // namespace pong::multimedia

#endif
