#include "Actions/Config.h"
#include "Actions/EmptyAction.h"

namespace Actions {
  namespace EmptyAction {
    uint8_t paramLength = 0;
    uint8_t instanceMax = Config::componentMax;
    uint8_t stateLength = 0;

    void start(void *state) { }
  }
}
