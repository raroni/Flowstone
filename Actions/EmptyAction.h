#ifndef ACTIONS_EMPTY_ACTION_H
#define ACTIONS_EMPTY_ACTION_H

#include <stdint.h>

namespace Actions {
  namespace EmptyAction {
    extern uint8_t instanceMax;
    extern uint8_t configLength;
    extern uint8_t stateLength;
    extern uint8_t paramLength;
    void start(void *state);
  }
}

#endif
