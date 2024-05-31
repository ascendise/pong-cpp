#include "multimedia.hpp"
#include <string>

namespace pong::multimedia {

const std::string &SystemEvent::getAction() const { return this->actionName; }

} // namespace pong::multimedia
