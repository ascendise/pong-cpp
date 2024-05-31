#ifndef MULTIMEDIA_DOUBLES_HPP
#define MULTIMEDIA_DOUBLES_HPP

#include "multimedia.hpp"

namespace pong::multimedia {

class SpySystemControl : public ISystemControl {
  ;

private:
  int exitCount = 0;

public:
  void exit() override { exitCount++; }

  int *getExitCountSpy() { return &exitCount; }
};

} // namespace pong::multimedia

#endif
