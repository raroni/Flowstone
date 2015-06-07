#ifndef ACTIONS_EMPTY_ACTION_H
#define ACTIONS_EMPTY_ACTION_H

#include <stdint.h>

namespace Actions {
  namespace EmptyAction {
    extern uint8_t paramLength;
    extern uint8_t instanceMax;
    extern uint8_t stateLength;
    void start(void *state);
  }
}

#endif
